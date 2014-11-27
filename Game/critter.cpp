#include "critter.h"

namespace TowerDefense {

Critter::Critter(Coordinate coord, const vector<Coordinate> &path, int level,
                 int hp, int speed, int reward)
    : HasCoordinate(coord), level(level), hp(hp), speed(speed), reward(reward),
      path(path) {}

void Critter::move() {
  hp -= damagePerTurn;
  if (numTurnsFrozen > 0)
    --numTurnsFrozen;
  else {
    pos = qMin<int>(pos + speed, path.size() - 1);
    this->coord = path.at(pos);
  }
  emit hpChanged(hp);
  emit moved(coord);
}

void Critter::hit(int attackDamage) {
  hp -= attackDamage;
  if (hp <= 0)
    emit death(reward);
}

void Critter::freeze(int turns) { numTurnsFrozen = turns; }

void Critter::burn(int damage) { damagePerTurn = damage; }

int Critter::getHp() const { return hp; }
}
