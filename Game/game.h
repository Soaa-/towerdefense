#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <vector>
#include <memory>
#include "Game/map.h"
#include "Game/tower.h"
#include "Game/critter.h"

namespace TowerDefense {

using std::vector;
using std::unique_ptr;

class Game : public QObject
{
  Q_OBJECT
private:
  int currency;
  unique_ptr<Map> map;
  vector<unique_ptr<Tower>> towers;
  vector<unique_ptr<Critter>> critters;

  void stepAdvanceCritters();
  void stepAttackCritters();

public:
  explicit Game(unique_ptr<Map> map, QObject *parent = 0);
  void placeTower(int x, int y, TowerType type);
  void run();

  Tower *getTower(int x, int y);

signals:
  void mapCellChanged(int x, int y, CellType type);
  void critterChanged(Critter &critter);
  void towerChanged(Tower &tower);
  void currencyChanged(int amount);
  void turnEnd();
  void gameOver();

public slots:
  void debitCurrency(int amount);

};

}

#endif // GAME_H
