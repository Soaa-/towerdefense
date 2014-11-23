#ifndef TARGETER_H
#define TARGETER_H

#include <vector>
#include "critter.h"

namespace TowerDefense {

class BaseTower;
using std::vector;

struct Targeter {
  virtual bool comparator(const Critter &rhs,
                          const Critter &lhs) = 0;
};

struct NearestToTowerTargeter : Targeter {
private:
  BaseTower &tower;
public:
  NearestToTowerTargeter(BaseTower &tower) : tower(tower) {}
  virtual bool comparator(const Critter &rhs,
                          const Critter &lhs);
};

struct NearestToExitTargeter : Targeter {
private:
  Coordinate &exit;
public:
  NearestToExitTargeter(Coordinate &exit) : exit(exit) {}
  virtual bool comparator(const Critter &rhs,
                          const Critter &lhs);
};

struct StrongestTargeter : Targeter {
  virtual bool comparator(const Critter &rhs,
                          const Critter &lhs);
};

struct WeakestTargeter : Targeter {
  virtual bool comparator(const Critter &rhs,
                          const Critter &lhs);
};
}

#endif // TARGETER_H
