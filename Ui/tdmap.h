#ifndef TDMAP_H
#define TDMAP_H

#include <QMainWindow>
#include <QErrorMessage>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <memory>
#include "Game/game.h"
#include "Game/map.h"
#include "Graphics/gamescene.h"
#include "placetowerdialog.h"
#include "createmapdialog.h"
#include "towerinspectordialog.h"

namespace Ui {
class TdMap;
}

using std::shared_ptr;

class TdMap : public QMainWindow
{
  Q_OBJECT
public:
  explicit TdMap(QWidget *parent = 0);
  ~TdMap();

private slots:
  void on_actionPurchase_Tower_triggered();
  void on_actionNew_Game_triggered();
  void on_actionLoad_Map_triggered();
  void on_actionSave_Map_triggered();
  void on_actionEnable_Draw_Map_Mode_triggered(bool checked);
  void on_actionSet_Entrance_triggered();
  void on_actionSet_Exit_triggered();

  void onOpenTowerInspector(BaseTower *tower);
  void onCashChange(int cash);

  void on_actionStart_Game_triggered();

  void on_actionGo_triggered();

private:
  Ui::TdMap *ui;
  GameScene *gameScene;
  Map *map;
  Game *game;

  void gameBegin();

  void setUiStateIdle();
  void setUiStatePlayIdle();
  void setUiStatePlayRun();
  void setUiStateEditMap();
};

#endif // TDMAP_H
