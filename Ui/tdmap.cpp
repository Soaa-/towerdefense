#include "tdmap.h"
#include "ui_tdmap.h"

using std::make_shared;

TdMap::TdMap(QWidget *parent) : QMainWindow(parent), ui(new Ui::TdMap) {
  ui->setupUi(this);
}

TdMap::~TdMap() { delete ui; }

void TdMap::on_actionPurchase_Tower_triggered() {
  auto dialog = new PlaceTowerDialog(this);
  if (dialog->exec()) {
    // TODO: Place Tower
  }
}

void TdMap::on_actionNew_Game_triggered() {
  auto dialog = new CreateMapDialog(this);
  if (dialog->exec()) {
    map = new Map(dialog->getHSize(), dialog->getVSize(), this);
    game = new Game(unique_ptr<Map>(map), this);
    // TODO: Make ownership semantics more consistent, maybe...
    gameScene = new GameScene(*game, this);
    ui->graphicsView->setScene(gameScene);
    gameBegin(); // TODO: Implement gameBegin()
  }
}

void TdMap::on_actionLoad_Map_triggered() {
  QString name = QFileDialog::getOpenFileName(this, "Open Map");
  QFile mapFile(name);
  if (!mapFile.open(QIODevice::ReadOnly | QIODevice::Text))
    return;
  QTextStream in(&mapFile);

  map = new Map(in, this);
  game = new Game(unique_ptr<Map>(map), this);
  gameScene = new GameScene(*game, this);
  ui->graphicsView->setScene(gameScene);
  gameBegin();
}

void TdMap::on_actionSave_Map_triggered() {
  if (map->isValid()) {
    QString name = QFileDialog::getSaveFileName(this, "Save Map As");
    QFile mapFile(name);
    if (!mapFile.open(QIODevice::WriteOnly | QIODevice::Text))
      return;
    QTextStream out(&mapFile);
    out << *map;
    mapFile.flush();
  } else {
    ui->statusBar->showMessage("Map is invalid!", 2000);
  }
}

void TdMap::on_actionEnable_Draw_Map_Mode_triggered(bool checked) {
  if (!checked)
    gameScene->setState(GameState::IDLE);
  else
    gameScene->setState(GameState::EDIT_MAP_DRAW);
}

void TdMap::on_actionSet_Entrance_triggered() {
  gameScene->setState(GameState::EDIT_MAP_SET_ENTRANCE);
}

void TdMap::on_actionSet_Exit_triggered() {
  gameScene->setState(GameState::EDIT_MAP_SET_EXIT);
}

void TdMap::onOpenTowerInspector(Tower &tower) {
  auto dialog = new TowerInspectorDialog(*game, tower, this);
  dialog->show();
  dialog->raise();
  dialog->activateWindow();
}

void TdMap::onCashChange(int cash) {
  ui->statusBar->showMessage(QString("Current cash: %1").arg(cash), 2000);
}

void TdMap::gameBegin() {}
