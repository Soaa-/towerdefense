#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "Game/game.h"

class GameScene : public QGraphicsScene
{
  Q_OBJECT
private:
  Game &game;
  MapItem *mapItem;
  QVector<TowerItem *> towerItems;
  QVector<CritterItem *> critterItems;

  enum class GameState {
    EDIT_MAP_DRAW,
    EDIT_MAP_SET_ENTRANCE,
    EDIT_MAP_SET_EXIT,
    PLAY_TURN,
    PLAY_INTERMISSION_SELECT_TOWER,
    PLAY_INTERMISSION_PLACE_TOWER
  };

public:
  explicit GameScene(QObject *parent = 0);

  virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

  void updateMap();

signals:

public slots:


};

#endif // GAMESCENE_H
