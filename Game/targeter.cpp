#include "targeter.h"
#include "tower.h"

namespace TowerDefense {

bool NearestToTowerTargeter::comparator(const Critter &rhs, const Critter &lhs) {
  return (tower.distanceTo(rhs) < tower.distanceTo(lhs));
}

bool NearestToExitTargeter::comparator(const Critter &rhs, const Critter &lhs) {
  return (exit.distanceTo(rhs.getCoord()) < exit.distanceTo(lhs.getCoord()));
}

bool StrongestTargeter::comparator(const Critter &rhs, const Critter &lhs) {
  return (rhs.getHp() > lhs.getHp());
}

bool WeakestTargeter::comparator(const Critter &rhs, const Critter &lhs) {
  return (rhs.getHp() < lhs.getHp());
}


}
