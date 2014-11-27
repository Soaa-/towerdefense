#include "towerinspectordialog.h"
#include "ui_towerinspectordialog.h"

TowerInspectorDialog::TowerInspectorDialog(Game *game, BaseTower *tower,
                                           QWidget *parent)
    : QDialog(parent), ui(new Ui::TowerInspectorDialog), game(game),
      tower(tower) {
  ui->setupUi(this);
  connect(this->tower, SIGNAL(levelChanged(int)), this, SLOT(updateStats(int)));
  updateStats();
}

TowerInspectorDialog::~TowerInspectorDialog() { delete ui; }

void TowerInspectorDialog::on_sellTowerButton_clicked() {}

void TowerInspectorDialog::on_UpgradeTowerButton_clicked() {
  if (game->debitCurrency(tower->getUpgradePrice()))
    tower->upgrade();
}

void TowerInspectorDialog::on_OKButton_clicked() { close(); }

void TowerInspectorDialog::updateStats(int) { updateStats(); }

void TowerInspectorDialog::updateStats() {
  ui->LevelField->setText(QString::number(tower->getLevel()));
  ui->AttackPowerField->setText(QString::number(tower->getAttackPower()));
  ui->AttackRangeField->setText(QString::number(tower->getAttackRange()));
  ui->RateOfFireField->setText(QString::number(tower->getRateOfFire()));
  ui->UpgradePriceField->setText(QString::number(tower->getUpgradePrice()));
  ui->RefundValueField->setText(QString::number(tower->getRefundValue()));

  QStringList types;
  for (auto type : tower->getEnhancementTypes()) {
    switch (type) {
    case TowerType::AOE:
      types.append("Area");
      break;
    case TowerType::SLOWING:
      types.append("Freeze");
      break;
    case TowerType::BURNING:
      types.append("Burn");
      break;
    default:
      break;
    }
  }
  if (types.empty()) types.append("Basic");
  ui->TypeField->setText(types.join(", "));
}
