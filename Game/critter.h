#ifndef CRITTERGROUP_H
#define CRITTERGROUP_H

#include <QObject>
#include "map.h"
#include "coordinate.h"

namespace TowerDefense {

class Critter : public QObject, public HasCoordinate {
  Q_OBJECT
private:
  int level;
  int hp;
  int speed;
  int reward;
  int numTurnsFrozen = 0;
  int damagePerTurn = 0;

  int pos = 0;
  const vector<Coordinate> &path;

public:
  Critter(Coordinate coord, const vector<Coordinate> &path, int level, int hp,
          int speed, int reward);
  ~Critter() {}

  void move();
  void hit(int attackDamage);
  void freeze(int turns);
  void burn(int damage);

  int getHp() const;

signals:
  void death(int reward);
  void moved(Coordinate coord);
  void hpChanged(int hp);
};

class CritterFactory {
private:
  CritterFactory();

public:
  static Critter *create(Map &map, int level) {
    int hp = 15 + level * 3;
    int speed = 1 + level / 3;
    int reward = 5 + level * 2;
    return new Critter(map.getEntrance(), map.getPath(), level, hp, speed,
                       reward);
  }
};

} // namespace TowerDefense

#endif // CRITTERGROUP_H
