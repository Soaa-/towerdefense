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
  PLAY_INTERMISSION_IDLE,
  PLAY_INTERMISSION_PLACE_TOWER,
  PLAY_RUN_TURN
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
  TowerType nextTowerType;

  void setState(GameState state);
public:

  explicit GameScene(Game &game, QObject *parent = 0);

  virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

  void updateMap();

  void setStateIdle();

  void setStatePlayIdle();
  void setStatePlaceTower(TowerType type);
  void setStatePlayRunTurn();

  void setStateEditDraw();
  void setStateEditSetEntrance();
  void setStateEditSetExit();


signals:

public slots:


};

#endif // GAMESCENE_H
