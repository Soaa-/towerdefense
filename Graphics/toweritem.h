#ifndef TOWERITEM_H
#define TOWERITEM_H

#include <QGraphicsObject>
#include <QPainter>
#include "Game/tower.h"

enum class TowerType {
  BASIC,
  AOE,
  FREEZE,
  BURN
};

class TowerItem : public QGraphicsObject {
  Q_OBJECT
private:
  TowerType type;
  int level;
  QPen pen;
  QBrush brush;

public:
  TowerItem(TowerType type, QGraphicsItem *parent = 0)
      : QGraphicsObject(parent), type(type), level(1), brush(Qt::SolidPattern) {
    switch (type) {
    case TowerType::BASIC:
      pen.setColor(QColor(127, 127, 127));
      brush.setColor(QColor(180, 180, 180));
      break;
    case TowerType::AOE:
      pen.setColor(QColor(127, 0, 0));
      brush.setColor(QColor(180, 0, 0));
      break;
    case TowerType::FREEZE:
      pen.setColor(QColor(127, 127, 0));
      brush.setColor(QColor(180, 180, 0));
      break;
    case TowerType::BURN:
      pen.setColor(QColor(31, 31, 31));
      brush.setColor(QColor(63, 63, 63));
      break;
    }
  }

  QRectF boundingRect() const { return QRectF(-1.0, 21.0, 22.0, 22.0); }

  void paint(QPainter *painter, const QStyleOptionGraphicsItem*,
             QWidget*) {
    const QPointF points[8] = {QPointF(5.0, 20.0), QPointF(5.0, 5.0),
                               QPointF(0.0, 5.0),  QPointF(0.0, 0.0),
                               QPointF(20.0, 0.0), QPointF(20.0, 5.0),
                               QPointF(15.0, 5.0), QPointF(15.0, 20.0)};
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawPolygon(points, 8);
    painter->setFont(QFont("Arial", 8));
    painter->drawText(10, 10, QString::number(level));
  }

public slots:
  void setLevel(int level, int) { this->level = level; }
};

#endif // TOWERITEM_H
