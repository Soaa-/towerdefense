#ifndef TOWERINSPECTORDIALOG_H
#define TOWERINSPECTORDIALOG_H

#include <QDialog>
#include "Game/game.h"
#include "Game/tower.h"

using namespace TowerDefense;

namespace Ui {
class TowerInspectorDialog;
}

class TowerInspectorDialog : public QDialog
{
  Q_OBJECT

public:
  TowerInspectorDialog(Game *game, BaseTower *tower, QWidget *parent = 0);
  ~TowerInspectorDialog();

private slots:
  void on_sellTowerButton_clicked();
  void on_UpgradeTowerButton_clicked();
  void on_OKButton_clicked();
  void updateStats(int);
  void updateStats();

private:
  Ui::TowerInspectorDialog *ui;

  Game *game;
  BaseTower *tower;
};

#endif // TOWERINSPECTORDIALOG_H
