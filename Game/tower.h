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

class BaseTower : public virtual IHasCoordinate {
protected:
  CritterVector &critters;

public:
  BaseTower(CritterVector &critters) : critters(critters) {}
  virtual ~BaseTower() {}

  void attack();

  virtual vector<Critter *> acquireTargets() = 0;
  virtual void attack(Critter &critter) = 0;

  virtual int getPurchasePrice() const = 0;
  virtual int getUpgradePrice() const = 0;
  virtual int getRefundValue() const = 0;
  virtual int getAttackRange() const = 0;
  virtual int getAttackPower() const = 0;
  virtual int getRateOfFire() const = 0;
  virtual int getLevel() const = 0;

  virtual vector<TowerType> getEnhancementTypes() const = 0;
};

class Tower : public QObject,
              public BaseTower,
              public HasCoordinate {
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

  virtual int getPurchasePrice() const { return purchasePrice; }
  virtual int getUpgradePrice() const { return upgradePrice; }
  virtual int getRefundValue() const { return refundValue; }
  virtual int getAttackRange() const { return attackRange; }
  virtual int getAttackPower() const { return attackPower; }
  virtual int getRateOfFire() const { return rateOfFire; }
  virtual int getLevel() const { return level; }

  virtual vector<TowerType> getEnhancementTypes() const;

public slots:
  void upgrade();

signals:
  void levelChanged(int newLevel, int cost);
};

class TowerEnhancement : public BaseTower {
protected:
  unique_ptr<BaseTower> tower;

  virtual vector<Critter *> acquireTargets() { return tower->acquireTargets(); }
  virtual void attack(Critter &critter) { tower->attack(critter); }

public:
  TowerEnhancement(CritterVector &critters, unique_ptr<BaseTower> tower)
      : BaseTower(critters), tower(std::move(tower)) {}
  virtual ~TowerEnhancement() {}

  virtual Coordinate getCoord() const { return tower->getCoord(); }
  virtual int distanceTo(const IHasCoordinate &other) const {
    return tower->distanceTo(other);
  }
  virtual int getPurchasePrice() const { return tower->getPurchasePrice(); }
  virtual int getUpgradePrice() const { return tower->getUpgradePrice(); }
  virtual int getRefundValue() const { return tower->getRefundValue(); }
  virtual int getAttackRange() const { return tower->getAttackRange(); }
  virtual int getAttackPower() const { return tower->getAttackPower(); }
  virtual int getRateOfFire() const { return tower->getRateOfFire(); }
  virtual int getLevel() const { return tower->getLevel(); }

  virtual void attack();
};

class AoeEnhancement : public TowerEnhancement {
protected:
  virtual vector<Critter *> acquireTargets();

public:
  AoeEnhancement(CritterVector &critters, unique_ptr<BaseTower> tower)
      : TowerEnhancement(critters, std::move(tower)) {}
  virtual ~AoeEnhancement() {}

  virtual vector<TowerType> getEnhancementTypes() const;
};

class SlowingEnhancement : public TowerEnhancement {
protected:
  virtual void attack(Critter &critter);

public:
  SlowingEnhancement(CritterVector &critters, unique_ptr<BaseTower> tower)
      : TowerEnhancement(critters, std::move(tower)) {}
  virtual ~SlowingEnhancement() {}

  virtual vector<TowerType> getEnhancementTypes() const;
};

class BurningEnhancement : public TowerEnhancement {
protected:
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
