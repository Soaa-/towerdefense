#include "gamescene.h"

GameScene::GameScene(Game *game, QObject *parent)
    : QGraphicsScene(parent), game(game) {
  mapItem = new MapItem(&game->getMap(), cellSize);
  this->addItem(mapItem);

  connect(game, SIGNAL(newCritter(Critter *)), this,
          SLOT(onNewCritter(Critter *)));
  connect(game, SIGNAL(newTower(BaseTower*)), this,
          SLOT(onNewTower(BaseTower*)));
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  QPointF pos = mouseEvent->scenePos();

  int cx = (int)pos.x() / cellSize;
  int cy = (int)pos.y() / cellSize;
  if (cx < 0 || cy < 0 || cx >= game->getMap().getSizeX() ||
      cy >= game->getMap().getSizeY())
    return;

  Coordinate coord(cx, cy);

  mouseEvent->accept();

  switch (state) {
  case GameState::EDIT_MAP_DRAW:
    mousePressDrawMap(mouseEvent, coord);
    break;
  case GameState::EDIT_MAP_SET_ENTRANCE:
    mousePressSetEntrance(mouseEvent, coord);
    break;
  case GameState::EDIT_MAP_SET_EXIT:
    mousePressSetExit(mouseEvent, coord);
    break;
  case GameState::PLAY_INTERMISSION_IDLE:
    mousePressSelectTower(mouseEvent, coord);
    break;
  case GameState::PLAY_INTERMISSION_PLACE_TOWER:
    mousePressPlaceTower(mouseEvent, coord);
    break;
  default:
    break;
  }
}

void GameScene::setStateIdle() { state = GameState::IDLE; }

void GameScene::setState(GameState state) { this->state = state; }

void GameScene::mousePressDrawMap(QGraphicsSceneMouseEvent *mouseEvent,
                                  Coordinate coord) {
  switch (mouseEvent->button()) {
  case Qt::LeftButton:
    game->getMap().setCellToType(coord, CellType::PATH);
    break;
  case Qt::RightButton:
    game->getMap().setCellToType(coord, CellType::SCENERY);
    break;
  default:
    break;
  }
}

void GameScene::mousePressSetEntrance(QGraphicsSceneMouseEvent *mouseEvent,
                                      Coordinate coord) {
  switch (mouseEvent->button()) {
  case Qt::LeftButton:
    game->getMap().setEntrance(coord);
    setStateEditDraw();
    break;
  default:
    break;
  }
}

void GameScene::mousePressSetExit(QGraphicsSceneMouseEvent *mouseEvent,
                                  Coordinate coord) {
  switch (mouseEvent->button()) {
  case Qt::LeftButton:
    game->getMap().setExit(coord);
    setStateEditDraw();
    break;
  default:
    break;
  }
}

void GameScene::mousePressSelectTower(QGraphicsSceneMouseEvent *mouseEvent,
                                      Coordinate coord) {
  auto tower = game->getTower(coord);
  switch (mouseEvent->button()) {
  case Qt::LeftButton:
    if (tower)
      emit towerSelected(tower);
    break;
  default:
    break;
  }
}

void GameScene::mousePressPlaceTower(QGraphicsSceneMouseEvent *mouseEvent,
                                     Coordinate coord) {
  switch (mouseEvent->button()) {
  case Qt::LeftButton:
    game->placeTower(coord, nextTowerType);
    setStatePlayIdle();
    break;
  default:
    break;
  }
}

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

void GameScene::onNewCritter(Critter *critter) {
  auto critterItem = new CritterItem(cellSize, critter->getHp());
  connect(critter, SIGNAL(moved(Coordinate)), critterItem,
          SLOT(onMove(Coordinate)));
  connect(critter, SIGNAL(hpChanged(int)), critterItem, SLOT(onHpChanged(int)));
  connect(critter, SIGNAL(death(int)), critterItem, SLOT(onDeath(int)));
  critterItem->onMove(critter->getCoord());
  this->addItem(critterItem);
}

void GameScene::onNewTower(BaseTower *tower) {
  auto towerItem = new TowerItem(cellSize, tower->getLevel(),
                                 TowerType::BASIC);
  connect(tower, SIGNAL(levelChanged(int, int)), towerItem,
          SLOT(setLevel(int, int)));
  towerItem->setCoord(tower->getCoord());
  this->addItem(towerItem);
}
