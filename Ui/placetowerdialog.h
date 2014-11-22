#ifndef PLACETOWERDIALOG_H
#define PLACETOWERDIALOG_H

#include <QDialog>
#include "Game/tower.h"

using TowerDefense::TowerType;

namespace Ui {
class PlaceTowerDialog;
}

class PlaceTowerDialog : public QDialog
{
  Q_OBJECT

public:
  explicit PlaceTowerDialog(QWidget *parent = 0);
  ~PlaceTowerDialog();

  TowerType getTowerType();

private:
  Ui::PlaceTowerDialog *ui;
};

#endif // PLACETOWERDIALOG_H
