#include "mapscene.h"
#include <QDebug>

QGraphicsRectItem *MapScene::placeCell(int x, int y, const QPen &pen,
                                       const QBrush &brush) {
  int sx = x * cellSize;
  int sy = y * cellSize;
  if (mapItems[y][x])
    this->removeItem(mapItems[y][x]);
  mapItems[y][x] = this->addRect(0, 0, cellSize, cellSize, pen, brush);
  mapItems[y][x]->setPos(sx, sy);
  return mapItems[y][x];
}

void MapScene::mousePressDefault(QGraphicsSceneMouseEvent *mouseEvent, int cx,
                                 int cy) {
  Tower *tower;
  switch (mouseEvent->button()) {
  case Qt::LeftButton:
    // tower = map->getCell(cx, cy)->getTower();
    if (tower) {
      emit selectedTower(tower);
    }
    break;
  default:
    break;
  }
}

void MapScene::mousePressDrawMap(QGraphicsSceneMouseEvent *mouseEvent, int cx,
                                 int cy) {
  switch (mouseEvent->button()) {
  case Qt::LeftButton:
    // map->setCellToType(cx, cy, CellType::PATH);
    break;
  case Qt::RightButton:
    // map->setCellToType(cx, cy, CellType::SCENERY);
    break;
  default:
    break;
  }
}

void MapScene::mousePressSetEntrance(QGraphicsSceneMouseEvent *mouseEvent,
                                     int cx, int cy) {
  switch (mouseEvent->button()) {
  case Qt::LeftButton:
    // map->setEntrance(cx, cy);
    break;
  default:
    break;
  }
  setState(MapUiState::DRAW_MAP);
}

void MapScene::mousePressSetExit(QGraphicsSceneMouseEvent *mouseEvent, int cx,
                                 int cy) {
  switch (mouseEvent->button()) {
  case Qt::LeftButton:
    // map->setExit(cx, cy);
    break;
  default:
    break;
  }
  setState(MapUiState::DRAW_MAP);
}

void MapScene::mousePressPlaceTower(QGraphicsSceneMouseEvent *mouseEvent,
                                    int cx, int cy) {
  Cell *cell;
  Tower *tower;
  switch (mouseEvent->button()) {
  case Qt::LeftButton:
    // map->placeTower(cx, cy, towerFactory(nextTowerType));
    // cell = map->getCell(cx, cy).get();
    tower = cell->getTower();
    if (!tower && cell->getType() == CellType::SCENERY)
      cell->placeTower(towerFactory(nextTowerType));
    break;
  default:
    break;
  }
  updateMap();
  setState(MapUiState::DEFAULT);
}

MapScene::MapScene(QObject *parent) : QGraphicsScene(parent), map(nullptr) {}

MapScene::MapScene(QObject *parent, shared_ptr<TowerDefense::Map> map)
    : QGraphicsScene(parent), map(map),
      mapItems(map->getSizeY(), QVector<QGraphicsRectItem *>(map->getSizeX())),
      pathPen(QColor(150, 75, 0)), pathBrush(QColor(150, 75, 0, 200)),
      entrancePen(QColor(150, 150, 0)), entranceBrush(QColor(150, 150, 0, 200)),
      exitPen(QColor(200, 0, 0)), exitBrush(QColor(200, 0, 0, 200)),
      sceneryPen(QColor(0, 180, 0)), sceneryBrush(QColor(0, 180, 0, 200)) {
  connect(map.get(), SIGNAL(stateChanged()), this, SLOT(updateMap()));
  updateMap();
}

void MapScene::setNextTowerType(TowerDefense::TowerType type) {
  nextTowerType = type;
}

void MapScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  QPointF pos = mouseEvent->scenePos();

  int cx = (int)pos.x() / cellSize;
  int cy = (int)pos.y() / cellSize;
  if (cx < 0 || cy < 0 || cx >= map->getSizeX() || cy >= map->getSizeY())
    return;

  mouseEvent->accept();

  switch (state) {
  case MapUiState::DEFAULT:
    mousePressDefault(mouseEvent, cx, cy);
    break;
  case MapUiState::DRAW_MAP:
    mousePressDrawMap(mouseEvent, cx, cy);
    break;
  case MapUiState::SET_ENTRANCE:
    mousePressSetEntrance(mouseEvent, cx, cy);
    break;
  case MapUiState::SET_EXIT:
    mousePressSetExit(mouseEvent, cx, cy);
    break;
  case MapUiState::PLACE_TOWER:
    mousePressPlaceTower(mouseEvent, cx, cy);
    break;
  default:
    break;
  }
}

void MapScene::updateMap() {
  for (int y = 0; y < map->getSizeY(); ++y)
    for (int x = 0; x < map->getSizeX(); ++x)
      if (map->getCellType(x, y) == CellType::PATH) {
        // draw appropriate color
        QGraphicsRectItem *cell;
        if (map->isEntrance(x, y))
          cell = placeCell(x, y, entrancePen, entranceBrush);
        else if (map->isExit(x, y))
          cell = placeCell(x, y, exitPen, exitBrush);
        else
          cell = placeCell(x, y, pathPen, pathBrush);
        // draw critter
        auto critter = map->getCell(x, y)->getCritter();
        if (critter) {
          auto critterItem = new CritterItem();
          critterItem->setParentItem(cell);
          connect(critter, SIGNAL(death()), critterItem, SLOT(death()));
        }
      }
      else {
        auto cell = placeCell(x, y, sceneryPen, sceneryBrush);
        auto tower = map->getCell(x, y)->getTower();
        if (tower) {
          auto towerItem = new TowerItem(tower->getType());
          towerItem->setParentItem(cell);
          connect(tower, SIGNAL(levelChanged(int, int)), towerItem,
                  SLOT(setLevel(int, int)));
        }
      }
}

void MapScene::setState(MapUiState state) {
  if (state == MapUiState::SET_ENTRANCE || state == MapUiState::SET_EXIT)
    if (this->state != MapUiState::DRAW_MAP)
      return;
  this->state = state;
}
