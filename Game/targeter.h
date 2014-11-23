#ifndef TARGETER_H
#define TARGETER_H

#include <vector>
#include "critter.h"

namespace TowerDefense {

using std::vector;

class Targeter {
public:
  Targeter();
  virtual vector<Critter *> getCrittersInRange() = 0;
};
}

#endif // TARGETER_H
