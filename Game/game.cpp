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
    }
    else
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
  } while (!critters.empty() && !isCritterAtExit());
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

bool Game::debitCurrency(int amount) {
  if (currency - amount < 0)
    return false;
  currency -= amount;
  return true;
}
}
