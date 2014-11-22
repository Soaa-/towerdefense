#ifndef TDMAP_H
#define TDMAP_H

#include <QMainWindow>
#include <QErrorMessage>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <memory>
#include "Game/map.h"
#include "Graphics/mapscene.h"
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

  void onOpenTowerInspector(Tower *tower);
  void onCashChange(int cash);

private:
  Ui::TdMap *ui;
  MapScene *mapScene;
  shared_ptr<TowerDefense::Map> map;
};

#endif // TDMAP_H