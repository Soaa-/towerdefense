#ifndef TOWERINSPECTORDIALOG_H
#define TOWERINSPECTORDIALOG_H

#include <QDialog>
#include "Game/map.h"
#include "Game/tower.h"

using namespace TowerDefense;

namespace Ui {
class TowerInspectorDialog;
}

class TowerInspectorDialog : public QDialog
{
  Q_OBJECT

public:
  explicit TowerInspectorDialog(QWidget *parent = 0);
  TowerInspectorDialog(QWidget *parent, Map *map, Tower *tower);
  ~TowerInspectorDialog();

private slots:
  void on_sellTowerButton_clicked();
  void on_UpgradeTowerButton_clicked();
  void on_OKButton_clicked();
  void updateStats(int, int);
  void updateStats();

private:
  Ui::TowerInspectorDialog *ui;

  Map *map;
  Tower *tower;
};

#endif // TOWERINSPECTORDIALOG_H
