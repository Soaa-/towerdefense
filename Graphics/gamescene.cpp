#include "gamescene.h"

GameScene::GameScene(Game &game, QObject *parent)
    : QGraphicsScene(parent), game(game) {
  mapItem = new MapItem(game.getMap(), 20);
  this->addItem(mapItem);
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {}

void GameScene::setStateIdle() { state = GameState::IDLE; }

void GameScene::setState(GameState state) { this->state = state; }

void GameScene::setStatePlayIdle() {
  state = GameState::PLAY_INTERMISSION_IDLE;
}

void GameScene::setStatePlaceTower(TowerType type) {
  state = GameState::PLAY_INTERMISSION_PLACE_TOWER;
  nextTowerType = type;
}

void GameScene::setStatePlayRunTurn() { state = GameState::PLAY_RUN_TURN; }

void GameScene::setStateEditDraw() { state = GameState::EDIT_MAP_DRAW; }

void GameScene::setStateEditSetEntrance() {
  state = GameState::EDIT_MAP_SET_ENTRANCE;
}

void GameScene::setStateEditSetExit() { state = GameState::EDIT_MAP_SET_EXIT; }
