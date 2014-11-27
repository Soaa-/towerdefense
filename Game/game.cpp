#include "game.h"
#include "sleep.h"
#include "QCoreApplication"

namespace TowerDefense {

void Game::stepAdvanceCritters() {
  for (auto &critter : critters)
    critter->move();
  if (numCrittersToGenerate != 0) {
    auto newCrt = CritterFactory::create(*map, level);
    critters.push_back(unique_ptr<Critter>(newCrt));
    connect(newCrt, SIGNAL(death(int)), this, SLOT(creditCurrency(int)));
    connect(newCrt, SIGNAL(death(Critter *)), this,
            SLOT(onCritterDeath(Critter *)));
    emit newCritter(newCrt);
    --numCrittersToGenerate;
  }
}

void Game::stepAttackCritters() {
  for (auto &tower : towers)
    tower->attack();
}

bool Game::isCritterAtExit() {
  for (auto &critter : critters)
    if (critter->getCoord() == map->getExit())
      return true;
  return false;
}

Game::Game(unique_ptr<Map> map, QObject *parent)
    : QObject(parent), map(std::move(map)), towerFactory(critters) {}

void Game::placeTower(Coordinate coord, TowerType type) {
  if (map->getCellType(coord) == CellType::PATH)
    return;
  else if (getTower(coord))
    return;
  else {
    auto tower = towerFactory.create(coord, type);
    if (debitCurrency(tower->getPurchasePrice())) {
      towers.push_back(unique_ptr<BaseTower>(tower));
      emit newTower(tower);
    } else
      delete tower;
  }
}

void Game::run() {
  map->generatePath();
  numCrittersToGenerate = 5 + level / 2;
  do {
    stepAdvanceCritters();
    QCoreApplication::processEvents();
    Sleep::msleep(200);
    stepAttackCritters();
    QCoreApplication::processEvents();
    Sleep::msleep(200);
    qDebug() << currency;
  } while ((!critters.empty() || numCrittersToGenerate > 0) &&
           !isCritterAtExit());
  ++level;
}

Map &Game::getMap() { return *map; }

BaseTower *Game::getTower(Coordinate coord) {
  for (auto const &tower : towers)
    if (tower->getCoord() == coord)
      return tower.get();
  return nullptr;
}

void Game::creditCurrency(int amount) { currency += amount; }

void Game::onCritterDeath(Critter *critter) {
  critters.erase(std::find_if(critters.begin(), critters.end(),
                              [&](unique_ptr<Critter> const &p)
                                  -> bool { return p.get() == critter; }),
                 critters.end());
}

bool Game::debitCurrency(int amount) {
  if (currency - amount < 0)
    return false;
  currency -= amount;
  return true;
}
}
