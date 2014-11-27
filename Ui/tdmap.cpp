#include "tdmap.h"
#include "ui_tdmap.h"

using std::make_shared;

TdMap::TdMap(QWidget *parent) : QMainWindow(parent), ui(new Ui::TdMap) {
  ui->setupUi(this);
  setUiStateIdle();
}

TdMap::~TdMap() { delete ui; }

void TdMap::on_actionPurchase_Tower_triggered() {
  auto dialog = new PlaceTowerDialog(this);
  if (dialog->exec()) {
    auto type = dialog->getTowerType();
    gameScene->setStatePlaceTower(type);
  }
}

void TdMap::on_actionNew_Game_triggered() {
  auto dialog = new CreateMapDialog(this);
  if (dialog->exec()) {
    map = new Map(dialog->getHSize(), dialog->getVSize());
    game = new Game(unique_ptr<Map>(map), this);
    gameScene = new GameScene(game, this);
    ui->graphicsView->setScene(gameScene);
    connect(gameScene, SIGNAL(towerSelected(BaseTower *)), this,
            SLOT(onOpenTowerInspector(BaseTower *)));
    setUiStateIdle();
  }
}

void TdMap::on_actionLoad_Map_triggered() {
  QString name = QFileDialog::getOpenFileName(this, "Open Map");
  QFile mapFile(name);
  if (!mapFile.open(QIODevice::ReadOnly | QIODevice::Text))
    return;
  QTextStream in(&mapFile);

  map = new Map(in);
  game = new Game(unique_ptr<Map>(map), this);
  gameScene = new GameScene(game, this);
  ui->graphicsView->setScene(gameScene);
  connect(gameScene, SIGNAL(towerSelected(BaseTower *)), this,
          SLOT(onOpenTowerInspector(BaseTower *)));
  setUiStateIdle();
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
  if (!checked) {
    setUiStateIdle();
    gameScene->setStateIdle();
  } else {
    setUiStateEditMap();
    gameScene->setStateEditDraw();
  }
}

void TdMap::on_actionSet_Entrance_triggered() {
  gameScene->setStateEditSetEntrance();
}

void TdMap::on_actionSet_Exit_triggered() { gameScene->setStateEditSetExit(); }

void TdMap::on_actionStart_Game_triggered() { gameBegin(); }

void TdMap::on_actionGo_triggered() {
  setUiStatePlayRun();
  game->run();
  setUiStatePlayIdle();
}

void TdMap::onOpenTowerInspector(BaseTower *tower) {
  auto dialog = new TowerInspectorDialog(game, tower, this);
  dialog->show();
  dialog->raise();
  dialog->activateWindow();
}

void TdMap::onCashChange(int cash) {
  ui->statusBar->showMessage(QString("Current cash: %1").arg(cash));
}

void TdMap::gameBegin() {
  if (game->getMap().isValid()) {
    setUiStatePlayIdle();
    gameScene->setStatePlayIdle();
  } else {
    ui->statusBar->showMessage("Map is invalid.");
  }
}

void TdMap::setUiStateIdle() {
  ui->actionEnable_Draw_Map_Mode->setEnabled(true);
  ui->actionSave_Map->setEnabled(true);

  ui->actionSet_Entrance->setVisible(false);
  ui->actionSet_Exit->setVisible(false);

  ui->actionStart_Game->setVisible(true);
  ui->actionGo->setVisible(false);
  ui->actionPurchase_Tower->setVisible(false);

  ui->statusBar->showMessage("Welcome to Tower Defense.");
}

void TdMap::setUiStatePlayIdle() {
  ui->actionEnable_Draw_Map_Mode->setEnabled(false);
  ui->actionSave_Map->setEnabled(false);

  ui->actionSet_Entrance->setVisible(false);
  ui->actionSet_Exit->setVisible(false);

  ui->actionStart_Game->setVisible(false);
  ui->actionGo->setVisible(true);
  ui->actionGo->setEnabled(true);
  ui->actionPurchase_Tower->setVisible(true);
  ui->actionPurchase_Tower->setEnabled(true);

  ui->statusBar->showMessage("Build your towers now.");
}

void TdMap::setUiStatePlayRun() {
  ui->actionGo->setEnabled(false);
  ui->actionPurchase_Tower->setEnabled(false);

  // TODO show wave #
}

void TdMap::setUiStateEditMap() {
  ui->actionGo->setVisible(false);
  ui->actionPurchase_Tower->setVisible(false);

  ui->actionEnable_Draw_Map_Mode->setEnabled(true);
  ui->actionSave_Map->setEnabled(true);

  ui->actionStart_Game->setVisible(false);
  ui->actionSet_Entrance->setVisible(true);
  ui->actionSet_Exit->setVisible(true);

  ui->statusBar->showMessage("Draw your map.");
}
