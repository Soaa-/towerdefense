#ifndef TOWERITEM_H
#define TOWERITEM_H

#include <QGraphicsObject>
#include <QPainter>
#include "Game/tower.h"
#include "Game/coordinate.h"

using TowerDefense::TowerType;
using TowerDefense::Coordinate;

class TowerItem : public QGraphicsObject {
  Q_OBJECT
private:
  int cellSize;
  TowerType type;
  int level;
  QPen pen;
  QBrush brush;

public:
  TowerItem(int cellSize, int level, TowerType type, QGraphicsItem *parent = 0);

  QRectF boundingRect() const;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem*,
             QWidget*);

  void setCoord(Coordinate coord);

public slots:
  void setLevel(int level);
};

#endif // TOWERITEM_H
