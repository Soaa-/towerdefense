#include "tower.h"

namespace TowerDefense {

Tower::Tower(int purchasePrice, int upgradePrice, int refundValue,
             int attackRange, int attackPower, int rateOfFire, int level,
             bool isAoe)
    : purchasePrice(purchasePrice), upgradePrice(upgradePrice),
      refundValue(refundValue), attackRange(attackRange),
      attackPower(attackPower), rateOfFire(rateOfFire), level(level),
      isAoe(isAoe) {}

Tower::Tower(const Tower &tower)
    : Tower(tower.purchasePrice, tower.upgradePrice, tower.refundValue,
            tower.attackRange, tower.attackPower, tower.rateOfFire, tower.level,
            tower.isAoe) {}

void Tower::upgrade() {
  ++level;
  attackPower *= 1.2;
  upgradePrice *= 1.5;
  refundValue *= 1.3;
  emit levelChanged(level, upgradePrice);
}

DirectDamageTower::DirectDamageTower()
    : Tower(50, 10, 10, 5, 10, 1, 1, false) {}

AoeDamageTower::AoeDamageTower() : Tower(75, 15, 15, 5, 10, 1, 1, true) {}

SlowingTower::SlowingTower() : Tower(50, 10, 10, 6, 10, 1, 1, false) {}

AdditionalDamageTower::AdditionalDamageTower()
  : Tower(75, 15, 15, 5, 14, 1, 1, false) {}

Tower *towerFactory(TowerType type)
{
  switch (type) {
  case TowerType::DIRECT_DAMAGE:
    return new DirectDamageTower();
  case TowerType::AOE_DAMAGE:
    return new AoeDamageTower();
  case TowerType::SLOWING:
    return new SlowingTower();
  case TowerType::ADDITIONAL_DAMAGE:
    return new AdditionalDamageTower();
  }
}

} // namespace TowerDefense
