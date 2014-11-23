#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include <vector>
#include <memory>
#include "coordinate.h"
#include "targeter.h"
#include "critter.h"

namespace TowerDefense {

using std::vector;
using std::unique_ptr;
using CritterVector = vector<unique_ptr<Critter>>;

enum class TowerType { BASIC, AOE, SLOWING, BURNING };

class BaseTower {
protected:
  CritterVector &critters;

  virtual vector<Critter *> acquireTargets() = 0;
  virtual void attack(Critter &critter) = 0;

public:
  BaseTower(CritterVector &critters) : critters(critters) {}
  virtual ~BaseTower() {}

  void attack();
  virtual vector<TowerType> getEnhancementTypes() const = 0;
};

class Tower : public QObject, public BaseTower, public HasCoordinate {
  Q_OBJECT
protected:
  int purchasePrice;
  int upgradePrice;
  int refundValue;
  int attackRange;
  int attackPower;
  int rateOfFire;
  int level;
  unique_ptr<Targeter> targeter;

  virtual vector<Critter *> acquireTargets();
  virtual void attack(Critter &target);

public:
  Tower(const CritterVector &critters, const Coordinate &coord,
        int purchasePrice, int upgradePrice, int refundValue, int attackRange,
        int attackPower, int rateOfFire);
  // Tower(const Tower &tower);
  virtual ~Tower() {}

  int getPurchasePrice() const { return purchasePrice; }
  int getUpgradePrice() const { return upgradePrice; }
  int getRefundValue() const { return refundValue; }
  int getAttackRange() const { return attackRange; }
  int getAttackPower() const { return attackPower; }
  int getRateOfFire() const { return rateOfFire; }
  int getLevel() const { return level; }

  virtual vector<TowerType> getEnhancementTypes() const;

public slots:
  void upgrade();

signals:
  void levelChanged(int newLevel, int cost);
};

class TowerEnhancement : public BaseTower {
private:
  unique_ptr<BaseTower> tower;

public:
  TowerEnhancement(CritterVector &critters, unique_ptr<BaseTower> tower)
      : BaseTower(critters), tower(std::move(tower)) {}
  virtual ~TowerEnhancement() {}
};

class AoeEnhancement : public TowerEnhancement {
protected:
  virtual vector<Critter *> acquireTargets();
  virtual void attack(Critter &critter);
public:
  AoeEnhancement(CritterVector &critters, unique_ptr<BaseTower> tower)
      : TowerEnhancement(critters, std::move(tower)) {}
  virtual ~AoeEnhancement() {}

  virtual vector<TowerType> getEnhancementTypes() const;
};

class SlowingEnhancement : public TowerEnhancement {
protected:
  virtual vector<Critter *> acquireTargets();
  virtual void attack(Critter &critter);
public:
  SlowingEnhancement(CritterVector &critters, unique_ptr<BaseTower> tower)
      : TowerEnhancement(critters, std::move(tower)) {}
  virtual ~SlowingEnhancement() {}

  virtual vector<TowerType> getEnhancementTypes() const;
};

class BurningEnhancement : public TowerEnhancement {
protected:
  virtual vector<Critter *> acquireTargets();
  virtual void attack(Critter &critter);
public:
  BurningEnhancement(CritterVector &critters, unique_ptr<BaseTower> tower)
      : TowerEnhancement(critters, std::move(tower)) {}
  virtual ~BurningEnhancement() {}

  virtual vector<TowerType> getEnhancementTypes() const;
};

class TowerFactory {
private:
  CritterVector &critters;

  BaseTower *createBasicTower(const Coordinate &coord) {
    return new Tower(critters, coord, 100, 15, 50, 4, 10, 1);
  }

  BaseTower *createAoeTower(const Coordinate &coord) {
    return new AoeEnhancement(
        critters, std::move(unique_ptr<BaseTower>(
                      new Tower(critters, coord, 200, 35, 120, 3, 8, 1))));
  }

  BaseTower *createSlowingTower(const Coordinate &coord) {
    return new SlowingEnhancement(
        critters, std::move(unique_ptr<BaseTower>(
                      new Tower(critters, coord, 150, 20, 70, 4, 8, 1))));
  }

  BaseTower *createBurningTower(const Coordinate &coord) {
    return new BurningEnhancement(
        critters, std::move(unique_ptr<BaseTower>(
                      new Tower(critters, coord, 170, 25, 90, 3, 5, 1))));
  }

public:
  TowerFactory(CritterVector &critters) : critters(critters) {}

  BaseTower *create(const Coordinate &coord, TowerType type) {
    switch (type) {
    case TowerType::BASIC:
      return createBasicTower(coord);
    case TowerType::AOE:
      return createAoeTower(coord);
    case TowerType::SLOWING:
      return createSlowingTower(coord);
    case TowerType::BURNING:
      return createBurningTower(coord);
    }
  }
};

} // namespace TowerDefense

#endif // TOWER_H
