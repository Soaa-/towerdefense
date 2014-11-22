#include "critteritem.h"

CritterItem::CritterItem(QGraphicsItem *parent)
    : QGraphicsObject(parent), pen(QColor(255, 0, 255)),
      brush(QColor(255, 127, 255)) {}

QRectF CritterItem::boundingRect() const { return QRectF(0, 0, 20, 20); }

void CritterItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                        QWidget *) {
  QPointF poly[] = {QPointF(5, 15), QPointF(10, 5), QPointF(15, 15)};

  painter->setPen(pen);
  painter->setBrush(brush);
  painter->drawPolygon(poly, 3);
}

void CritterItem::death()
{

}
