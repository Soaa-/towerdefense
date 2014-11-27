#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "Game/game.h"
#include "Graphics/mapitem.h"
#include "Graphics/toweritem.h"
#include "Graphics/critteritem.h"

using namespace TowerDefense;

enum class GameState {
  IDLE,
  EDIT_MAP_DRAW,
  EDIT_MAP_SET_ENTRANCE,
  EDIT_MAP_SET_EXIT,
  PLAY_TURN,
  PLAY_INTERMISSION_SELECT_TOWER,
  PLAY_INTERMISSION_PLACE_TOWER
};

class GameScene : public QGraphicsScene
{
  Q_OBJECT
private:
  Game &game;
  MapItem *mapItem;
  QVector<TowerItem *> towerItems;
  QVector<CritterItem *> critterItems;

  GameState state;

public:

  explicit GameScene(Game &game, QObject *parent = 0);

  virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

  void updateMap();
  void setState(GameState state);

signals:

public slots:


};

#endif // GAMESCENE_H
