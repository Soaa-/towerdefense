#include "tower.h"

namespace TowerDefense {

Tower::Tower(const CritterVector &critters, const Coordinate &coord,
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

void Tower::acquireTargets() {}

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

vector<TowerType> AoeEnhancement::getEnhancementTypes() const {
  return tower->getEnhancementTypes().push_back(TowerType::AOE);
}

vector<TowerType> SlowingEnhancement::getEnhancementTypes() const {
  return tower->getEnhancementTypes().push_back(TowerType::SLOWING);
}

vector<TowerType> BurningEnhancement::getEnhancementTypes() const {
  return tower->getEnhancementTypes().push_back(TowerType::BURNING);
}

} // namespace TowerDefense
