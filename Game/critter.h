#ifndef CRITTERGROUP_H
#define CRITTERGROUP_H

#include <QObject>
#include "coordinate.h"

namespace TowerDefense {

class Critter : public QObject, public HasCoordinate {
  Q_OBJECT
private:
  int level;
  int hp;
  int speed;
  int reward;
  int numTurnsFrozen;
  int damagePerTurn;

public:
  Critter(Coordinate coord, int level, int hp, int speed, int reward)
      : HasCoordinate(coord), level(level), hp(hp), speed(speed),
        reward(reward) {}
  ~Critter() {}

  void move() {
    hp -= damagePerTurn;
    if (numTurnsFrozen > 0)
      --numTurnsFrozen;
    else
      this->coord += coord;
  }

  void hit(int attackDamage) {
    hp -= attackDamage;
    if (hp <= 0)
      emit death(reward);
  }

  void freeze(int turns) { numTurnsFrozen = turns; }
  void burn(int damage) { damagePerTurn = damage; }

  int getHp() const { return hp; }

signals:
  void death(int reward);
};

class CritterFactory {
private:
  CritterFactory();

public:
  static Critter *create(Coordinate coord, int level) {
    int hp = 15 + level * 3;
    int speed = 1 + level / 3;
    int reward = 5 + level * 2;
    return new Critter(coord, level, hp, speed, reward);
  }
};

} // namespace TowerDefense

#endif // CRITTERGROUP_H
