#ifndef CRITTERITEM_H
#define CRITTERITEM_H

#include <QGraphicsObject>
#include <QPainter>
#include "Game/coordinate.h"

using TowerDefense::Coordinate;

class CritterItem : public QGraphicsObject {
  Q_OBJECT
private:
  int cellSize;
  QPen pen;
  QBrush brush;

  int hp;

public:
  CritterItem(int cellSize, int hp, QGraphicsItem *parent = 0);

  virtual QRectF boundingRect() const;
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*,
             QWidget*);
signals:

public slots:
  void onDeath(int);
  void onMove(Coordinate coord);
  void onHpChanged(int hp);
};

#endif // CRITTERITEM_H
