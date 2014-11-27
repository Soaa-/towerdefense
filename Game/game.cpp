#include "game.h"

namespace TowerDefense {

void Game::stepAdvanceCritters() {
  for (auto &critter : critters)
    critter->move();
  if (numCrittersToGenerate != 0) {
    auto newCritter = CritterFactory::create(map->getEntrance(), level);
    critters.push_back(unique_ptr<Critter>(newCritter));
    --numCrittersToGenerate;
  }
}

void Game::stepAttackCritters() {
  for (auto &tower : towers)
    tower->attack();
}

Game::Game(unique_ptr<Map> map, QObject *parent)
    : QObject(parent), map(std::move(map)), towerFactory(critters) {}

void Game::placeTower(Coordinate coord, TowerType type) {
  if (map->getCellType(coord) == CellType::PATH)
    return;
  else if (getTower(coord))
    return;
  else {
    towers.push_back(unique_ptr<BaseTower>(towerFactory.create(coord, type)));
  }
}

void Game::run() {
  while (!critters.empty()) {
    stepAdvanceCritters();
    stepAttackCritters();
  }
}

BaseTower *Game::getTower(Coordinate coord) {
  for (auto const &tower : towers)
    if (tower->getCoord() == coord)
      return tower.get();
  return nullptr;
}

bool Game::debitCurrency(int amount) {
  if (currency - amount < 0)
    return false;
  currency -= amount;
  return true;
}

}
