#include "tower.h"

namespace TowerDefense {

Tower::Tower(CritterVector &critters, const Coordinate &coord,
             int purchasePrice, int upgradePrice, int refundValue,
             int attackRange, int attackPower, int rateOfFire)
    : BaseTower(critters), HasCoordinate(coord), purchasePrice(purchasePrice),
      upgradePrice(upgradePrice), refundValue(refundValue),
      attackRange(attackRange), attackPower(attackPower),
      rateOfFire(rateOfFire), level(1) {}

vector<TowerType> Tower::getEnhancementTypes() const {
  return vector<TowerType>();
}

vector<Critter *> Tower::acquireTargets() {
  auto range = getAttackRange();
  vector<Critter *> result;
  for (auto &critter : critters)
    if (distanceTo(*critter) <= range)
      result.push_back(critter.get());
  // std::sort(result.begin(), result.end(), targeter);
  if (result.empty())
    return vector<Critter *>();
  else
    return vector<Critter *>(1, result[0]);
}

void Tower::attack(Critter &target) { target.hit(attackPower); }

void Tower::upgrade() {
  ++level;
  attackPower *= 1.2;
  upgradePrice *= 1.5;
  refundValue *= 1.3;
  emit levelChanged(level);
}

void BaseTower::attack() {
  auto targets = this->acquireTargets();
  for (auto target : targets)
    this->attack(*target);
}

vector<Critter *> AoeEnhancement::acquireTargets() {
  auto range = getAttackRange();
  vector<Critter *> result;
  for (auto &critter : critters)
    if (distanceTo(*critter) <= range)
      result.push_back(critter.get());
  return result;
}

vector<TowerType> AoeEnhancement::getEnhancementTypes() const {
  auto ret = tower->getEnhancementTypes();
  ret.push_back(TowerType::AOE);
  return ret;
}

void SlowingEnhancement::attack(Critter &critter) { critter.freeze(3); }

vector<TowerType> SlowingEnhancement::getEnhancementTypes() const {
  auto ret = tower->getEnhancementTypes();
  ret.push_back(TowerType::SLOWING);
  return ret;
}

void BurningEnhancement::attack(Critter &critter) { critter.burn(5); }

vector<TowerType> BurningEnhancement::getEnhancementTypes() const {
  auto ret = tower->getEnhancementTypes();
  ret.push_back(TowerType::BURNING);
  return ret;
}



} // namespace TowerDefense
