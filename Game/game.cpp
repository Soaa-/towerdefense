#include "game.h"

namespace TowerDefense {

Game::Game(unique_ptr<Map> map, QObject *parent) : QObject(parent) {}

void Game::placeTower(int x, int y, TowerType type) {}

void Game::run() {}

void Game::debitCurrency(int amount) {}
}
