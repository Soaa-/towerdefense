#ifndef ATTACK_H
#define ATTACK_H

namespace TowerDefense {

class Attack {
private:
  int damage;
  int burnLevel;
  int slowLevel;

public:
  Attack(int damage, int burnLevel, int slowLevel)
      : damage(damage), burnLevel(burnLevel), slowLevel(slowLevel) {}

  int getDamage() const { return damage; }
  int getBurnLevel() const { return burnLevel; }
  int getSlowLevel() const { return slowLevel; }
};
}
#endif // ATTACK_H
