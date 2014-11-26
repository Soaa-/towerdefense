#include "tower.h"

namespace TowerDefense {

Tower::Tower(CritterVector &critters, const Coordinate &coord,
             int purchasePrice, int upgradePrice, int refundValue,
             int attackRange, int attackPower, int rateOfFire)
    : BaseTower(critters), HasCoordinate(coord), purchasePrice(purchasePrice),
      upgradePrice(upgradePrice), refundValue(refundValue),
      attackRange(attackRange), attackPower(attackPower),
      rateOfFire(rateOfFire), level(1) {}

Tower::Tower(const Tower &tower)
    : Tower(tower.coord, tower.purchasePrice, tower.upgradePrice,
            tower.refundValue, tower.attackRange, tower.attackPower,
            tower.rateOfFire, tower.level) {}

vector<TowerType> Tower::getEnhancementTypes() const {
  return vector<TowerType>();
}

vector<Critter *> Tower::acquireTargets() {
  auto range = getAttackRange();
  vector<Critter *> result;
  for (auto critter : critters)
    if (distanceTo(critter) <= range)
      result.push_back(critter.get());
  std::sort(result.begin(), result.end(), targeter->comparator);
  vector<Critter *> ret(1, result[0]);
  return ret;
}

void Tower::attack(Critter &target) { target->hit(attackPower); }

void Tower::upgrade() {
  ++level;
  attackPower *= 1.2;
  upgradePrice *= 1.5;
  refundValue *= 1.3;
  emit levelChanged(level, upgradePrice);
}

void BaseTower::attack() {
  auto targets = this->acquireTargets();
  for (auto target : targets)
    this->attack(*target);
}

vector<Critter *> AoeEnhancement::acquireTargets() {
  auto range = getAttackRange();
  vector<Critter *> result;
  for (auto critter : critters)
    if (distanceTo(critter) <= range)
      result.push_back(critter.get());
  return result;
}

void AoeEnhancement::attack(Critter &critter) { tower->attack(critter); }

vector<TowerType> AoeEnhancement::getEnhancementTypes() const {
  return tower->getEnhancementTypes().push_back(TowerType::AOE);
}

vector<TowerType> SlowingEnhancement::getEnhancementTypes() const {
  return tower->getEnhancementTypes().push_back(TowerType::SLOWING);
}

vector<TowerType> BurningEnhancement::getEnhancementTypes() const {
  return tower->getEnhancementTypes().push_back(TowerType::BURNING);
}

void TowerEnhancement::attack() { tower->attack(); }

} // namespace TowerDefense
