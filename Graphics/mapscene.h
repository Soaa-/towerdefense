#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QVector>
#include <QPoint>
#include <memory>
#include "Game/map.h"
#include "Game/tower.h"
#include "Graphics/toweritem.h"
#include "Graphics/critteritem.h"

using std::shared_ptr;
using std::unique_ptr;
using namespace TowerDefense;

enum class MapUiState {
  DEFAULT,
  DRAW_MAP,
  SET_ENTRANCE,
  SET_EXIT,
  PLACE_TOWER
};

class MapScene : public QGraphicsScene {
  Q_OBJECT
private:
  MapUiState state;
  shared_ptr<Map> map;
  QVector<QVector<QGraphicsRectItem *>> mapItems;
  QPen pathPen;
  QBrush pathBrush;
  QPen entrancePen;
  QBrush entranceBrush;
  QPen exitPen;
  QBrush exitBrush;
  QPen sceneryPen;
  QBrush sceneryBrush;
  const int cellSize = 20;

  TowerType nextTowerType;

  QGraphicsRectItem *placeCell(int x, int y, const QPen &pen,
                               const QBrush &brush);
  void mousePressDefault(QGraphicsSceneMouseEvent *mouseEvent, int cx, int cy);
  void mousePressDrawMap(QGraphicsSceneMouseEvent *mouseEvent, int cx, int cy);
  void mousePressSetEntrance(QGraphicsSceneMouseEvent *mouseEvent, int cx,
                             int cy);
  void mousePressSetExit(QGraphicsSceneMouseEvent *mouseEvent, int cx, int cy);
  void mousePressPlaceTower(QGraphicsSceneMouseEvent *mouseEvent, int cx,
                            int cy);

public:
  explicit MapScene(QObject *parent = 0);
  MapScene(QObject *parent, shared_ptr<Map> map);

  void setNextTowerType(TowerType type);

protected:
  virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

signals:
  void selectedTower(Tower *tower);

public slots:
  void updateMap();
  void setState(MapUiState state);
};

#endif // MAPSCENE_H
