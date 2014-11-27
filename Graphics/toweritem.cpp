#include "toweritem.h"

TowerItem::TowerItem(int cellSize, int level, TowerDefense::TowerType type,
                     QGraphicsItem *parent)
    : QGraphicsObject(parent), cellSize(cellSize), type(type), level(level),
      brush(Qt::SolidPattern) {
  switch (type) {
  case TowerType::BASIC:
    pen.setColor(QColor(127, 127, 127));
    brush.setColor(QColor(180, 180, 180));
    break;
  case TowerType::AOE:
    pen.setColor(QColor(127, 0, 0));
    brush.setColor(QColor(180, 0, 0));
    break;
  case TowerType::SLOWING:
    pen.setColor(QColor(127, 127, 0));
    brush.setColor(QColor(180, 180, 0));
    break;
  case TowerType::BURNING:
    pen.setColor(QColor(31, 31, 31));
    brush.setColor(QColor(63, 63, 63));
    break;
  }
}

QRectF TowerItem::boundingRect() const {
  return QRectF(-1.0, -1.0, 22.0, 22.0);
}

void TowerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                      QWidget *) {
  const QPointF points[8] = {QPointF(5.0, 20.0), QPointF(5.0, 5.0),
                             QPointF(0.0, 5.0),  QPointF(0.0, 0.0),
                             QPointF(20.0, 0.0), QPointF(20.0, 5.0),
                             QPointF(15.0, 5.0), QPointF(15.0, 20.0)};
  painter->setPen(pen);
  painter->setBrush(brush);
  painter->drawPolygon(points, 8);
  painter->setPen(Qt::SolidLine);
  painter->setFont(QFont("Arial", 8));
  painter->drawText(10, 10, QString::number(level));
}

void TowerItem::setCoord(TowerDefense::Coordinate coord) {
  auto wx = coord.x * cellSize;
  auto wy = coord.y * cellSize;
  this->setPos(wx, wy);
  update(boundingRect());
}

void TowerItem::setLevel(int level, int) {
  this->level = level;
  update(boundingRect());
}
