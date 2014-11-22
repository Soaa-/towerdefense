#include "towerinspectordialog.h"
#include "ui_towerinspectordialog.h"

TowerInspectorDialog::TowerInspectorDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::TowerInspectorDialog) {
  ui->setupUi(this);
}

TowerInspectorDialog::TowerInspectorDialog(QWidget *parent, Map *map,
                                           Tower *tower)
    : TowerInspectorDialog(parent) {
  this->map = map;
  this->tower = tower;
  connect(this->tower, SIGNAL(levelChanged(int, int)), this,
          SLOT(updateStats(int, int)));
  updateStats();
}

TowerInspectorDialog::~TowerInspectorDialog() { delete ui; }

void TowerInspectorDialog::on_sellTowerButton_clicked() {}

void TowerInspectorDialog::on_UpgradeTowerButton_clicked() {
  if (map->deductCash(tower->getUpgradePrice()))
    tower->upgrade();
}

void TowerInspectorDialog::on_OKButton_clicked() { close(); }

void TowerInspectorDialog::updateStats(int, int) { updateStats(); }

void TowerInspectorDialog::updateStats() {
  ui->LevelField->setText(QString::number(tower->getLevel()));
  ui->AttackPowerField->setText(QString::number(tower->getAttackPower()));
  ui->AttackRangeField->setText(QString::number(tower->getAttackRange()));
  ui->RateOfFireField->setText(QString::number(tower->getRateOfFire()));
  ui->UpgradePriceField->setText(QString::number(tower->getUpgradePrice()));
  ui->RefundValueField->setText(QString::number(tower->getRefundValue()));

  switch (tower->getType()) {
  case TowerType::DIRECT_DAMAGE:
    ui->TypeField->setText("Direct Damage");
    break;
  case TowerType::AOE_DAMAGE:
    ui->TypeField->setText("Area Damage");
    break;
  case TowerType::SLOWING:
    ui->TypeField->setText("Slowing");
    break;
  case TowerType::ADDITIONAL_DAMAGE:
    ui->TypeField->setText("Additional Damage");
    break;
  }
}
