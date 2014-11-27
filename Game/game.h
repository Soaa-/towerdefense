#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <vector>
#include <memory>
#include "map.h"
#include "tower.h"
#include "critter.h"

namespace TowerDefense {

using std::vector;
using std::unique_ptr;

class Game : public QObject
{
  Q_OBJECT
private:
  int level = 1;
  bool isGameOver = false;
  int numCrittersToGenerate;
  int currency = 500;
  unique_ptr<Map> map;
  vector<unique_ptr<BaseTower>> towers;
  vector<unique_ptr<Critter>> critters;

  TowerFactory towerFactory;

  void stepAdvanceCritters();
  void stepAttackCritters();
  bool isCritterAtExit();

public:
  explicit Game(unique_ptr<Map> map, QObject *parent = 0);
  ~Game() {}

  void placeTower(Coordinate coord, TowerType type);
  void upgradeTower(Coordinate coord);
  bool debitCurrency(int amount);

  void run();

  Map &getMap();
  BaseTower *getTower(Coordinate coord);

signals:
  void mapCellChanged(int x, int y, CellType type);
  void newCritter(Critter *critter);
  void newTower(BaseTower *tower);
  void currencyChanged(int amount);
  void turnEnd();
  void gameOver();

public slots:
  void creditCurrency(int amount);

};

}

#endif // GAME_H
