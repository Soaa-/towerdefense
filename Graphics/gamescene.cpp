#include "gamescene.h"

GameScene::GameScene(Game &game, QObject *parent)
  : QGraphicsScene(parent), game(game) {
  mapItem = new MapItem(game.getMap(), 20);
  this->addItem(mapItem);
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

}

void GameScene::setState(GameState state) { this->state = state; }
