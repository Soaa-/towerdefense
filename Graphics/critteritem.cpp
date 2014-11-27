#include "critteritem.h"

CritterItem::CritterItem(int cellSize, int hp, QGraphicsItem *parent)
    : QGraphicsObject(parent), cellSize(cellSize), pen(QColor(255, 0, 255)),
      brush(QColor(255, 127, 255)), hp(hp) {}

QRectF CritterItem::boundingRect() const { return QRectF(0, 0, 20, 20); }

void CritterItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                        QWidget *) {
  QPointF poly[] = {QPointF(5, 15), QPointF(10, 5), QPointF(15, 15)};

  painter->setPen(pen);
  painter->setBrush(brush);
  painter->drawPolygon(poly, 3);
  painter->setPen(Qt::SolidLine);
  painter->setFont(QFont("Arial", 8));
  painter->drawText(10, 10, QString::number(hp));
}

void CritterItem::onDeath(int) {
  this->deleteLater();
}

void CritterItem::onMove(Coordinate coord) {
  auto x = coord.x * cellSize;
  auto y = coord.y * cellSize;
  setPos(x, y);
  update(boundingRect());
}

void CritterItem::onHpChanged(int hp) {
  this->hp = hp;
  update(boundingRect());
}
