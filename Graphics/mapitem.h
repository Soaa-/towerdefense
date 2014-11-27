#ifndef MAPITEM_H
#define MAPITEM_H

#include <QGraphicsObject>
#include <QBrush>
#include <QPen>
#include <QVector>
#include <Game/map.h>
#include <Game/coordinate.h>

using namespace TowerDefense;

class MapItem : public QGraphicsObject {
  Q_OBJECT
private:
  Map &map;
  Coordinate entrance;
  Coordinate exit;

  int cellSize;
  QVector<QVector<QGraphicsRectItem *>> grid;

  QBrush entranceBrush;
  QBrush exitBrush;
  QBrush pathBrush;
  QBrush sceneryBrush;

  void drawMap();

public:
  explicit MapItem(Map &map, int cellSize, QGraphicsItem *parent = 0);

  virtual QRectF boundingRect() const;
  virtual void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);

signals:

public slots:
  void onCellTypeChanged(Coordinate coord, CellType type);
  void onEntranceChanged(Coordinate coord);
  void onExitChanged(Coordinate coord);
};

#endif // MAPITEM_H
