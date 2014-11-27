#include "mapitem.h"

void MapItem::drawMap() {
  for (int y = 0; y < map->getSizeY(); ++y) {
    for (int x = 0; x < map->getSizeX(); ++x) {
      Coordinate coord(x, y);
      switch (map->getCellType(coord)) {
      case CellType::PATH:
        if (map->isEntrance(coord)) {
          grid[y][x]->setBrush(entranceBrush);
          entrance = coord;
        } else if (map->isExit(coord)) {
          grid[y][x]->setBrush(exitBrush);
          exit = coord;
        } else
          grid[y][x]->setBrush(pathBrush);
        break;
      case CellType::SCENERY:
        grid[y][x]->setBrush(sceneryBrush);
        break;
      }
    }
  }
}

// TODO: track whether entrance/exit are set; if unset do not unset them again
MapItem::MapItem(Map *map, int cellSize, QGraphicsItem *parent)
    : QGraphicsObject(parent), map(map), entrance(map->getEntrance()),
      exit(map->getExit()), cellSize(cellSize),
      grid(map->getSizeY(), QVector<QGraphicsRectItem *>(map->getSizeX())),
      entranceBrush(QColor(150, 150, 0)), exitBrush(QColor(200, 0, 0)),
      pathBrush(QColor(150, 75, 0)), sceneryBrush(QColor(0, 180, 0)) {
  for (int y = 0; y < map->getSizeY(); ++y)
    for (int x = 0; x < map->getSizeX(); ++x) {
      int wx = cellSize * x;
      int wy = cellSize * y;
      grid[y][x] = new QGraphicsRectItem(0, 0, cellSize, cellSize, this);
      grid[y][x]->setPos(wx, wy);
      grid[y][x]->setPen(QPen(Qt::NoPen));
    }
  connect(map, SIGNAL(cellTypeChanged(Coordinate, CellType)), this,
          SLOT(onCellTypeChanged(Coordinate, CellType)));
  connect(map, SIGNAL(entranceChanged(Coordinate)), this,
          SLOT(onEntranceChanged(Coordinate)));
  connect(map, SIGNAL(exitChanged(Coordinate)), this,
          SLOT(onExitChanged(Coordinate)));
  drawMap();
}

QRectF MapItem::boundingRect() const { return QRectF(0, 0, 0, 0); }

void MapItem::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) {}

void MapItem::onCellTypeChanged(Coordinate coord, CellType type) {
  switch (type) {
  case CellType::SCENERY:
    grid[coord.y][coord.x]->setBrush(sceneryBrush);
    break;
  case CellType::PATH:
    grid[coord.y][coord.x]->setBrush(pathBrush);
  }
  update();
}

void MapItem::onEntranceChanged(Coordinate coord) {
  grid[entrance.y][entrance.x]->setBrush(pathBrush);
  grid[coord.y][coord.x]->setBrush(entranceBrush);
  entrance = coord;
  update();
}

void MapItem::onExitChanged(Coordinate coord) {
  grid[exit.y][exit.x]->setBrush(pathBrush);
  grid[coord.y][coord.x]->setBrush(exitBrush);
  exit = coord;
  update();
}
