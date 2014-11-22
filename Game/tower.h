#ifndef TOWER_H
#define TOWER_H

#include <QObject>

namespace TowerDefense {

enum class TowerType { DIRECT_DAMAGE, AOE_DAMAGE, SLOWING, ADDITIONAL_DAMAGE };

class Tower : public QObject {
  Q_OBJECT
protected:
  int purchasePrice;
  int upgradePrice;
  int refundValue;
  int attackRange;
  int attackPower;
  int rateOfFire;
  int level;
  bool isAoe;

  Tower(int purchasePrice, int upgradePrice, int refundValue, int attackRange,
        int attackPower, int rateOfFire, int level, bool isAoe);

public:
  Tower(const Tower& tower);
  virtual ~Tower() {}

  int getPurchasePrice() const { return purchasePrice; }
  int getUpgradePrice() const { return upgradePrice; }
  int getRefundValue() const { return refundValue; }
  int getAttackRange() const { return attackRange; }
  int getAttackPower() const { return attackPower; }
  int getRateOfFire() const { return rateOfFire; }
  int getLevel() const { return level; }
  bool getIsAoe() const { return isAoe; }

  virtual TowerType getType() = 0;

public slots:
  void upgrade();

signals:
  void levelChanged(int newLevel, int cost);
};

class DirectDamageTower : public Tower {
public:
  DirectDamageTower();
  virtual TowerType getType() { return TowerType::DIRECT_DAMAGE; }
};

class AoeDamageTower : public Tower {
public:
  AoeDamageTower();
  virtual TowerType getType() { return TowerType::AOE_DAMAGE; }
};

class SlowingTower : public Tower {
public:
  SlowingTower();
  virtual TowerType getType() { return TowerType::SLOWING; }
};

class AdditionalDamageTower : public Tower {
public:
  AdditionalDamageTower();
  virtual TowerType getType() { return TowerType::ADDITIONAL_DAMAGE; }
};

Tower *towerFactory(TowerType type);

} // namespace TowerDefense

#endif // TOWER_H
