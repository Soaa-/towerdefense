#ifndef CRITTERGROUP_H
#define CRITTERGROUP_H

#include <QObject>

namespace TowerDefense {

class Critter : public QObject {
  Q_OBJECT
private:
  int level;
  int hp;
  int speed;
  int reward;

public:
  Critter(int level);
  ~Critter() {}

public slots:
  void hit(int attackDamage) {
    hp -= attackDamage;
    if (hp <= 0)
      emit death();
  }

signals:
  void death();

};

} // namespace TowerDefense

#endif // CRITTERGROUP_H
