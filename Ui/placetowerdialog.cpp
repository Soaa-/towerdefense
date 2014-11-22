#include "placetowerdialog.h"
#include "ui_placetowerdialog.h"

PlaceTowerDialog::PlaceTowerDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::PlaceTowerDialog)
{
  ui->setupUi(this);
}

PlaceTowerDialog::~PlaceTowerDialog()
{
  delete ui;
}

TowerType PlaceTowerDialog::getTowerType()
{
  switch (ui->TowerTypeBox->currentIndex()) {
  case 0:
    return TowerType::DIRECT_DAMAGE;
  case 1:
    return TowerType::AOE_DAMAGE;
  case 2:
    return TowerType::SLOWING;
  case 3:
    return TowerType::ADDITIONAL_DAMAGE;
  }
}
