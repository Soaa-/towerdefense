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
    mapScene->setNextTowerType(dialog->getTowerType());
    mapScene->setState(MapUiState::PLACE_TOWER);
  }
}

void TdMap::on_actionNew_Game_triggered() {
  auto dialog = new CreateMapDialog(this);
  if (dialog->exec()) {
    map =
        make_shared<TowerDefense::Map>(dialog->getHSize(), dialog->getVSize());
    mapScene = new MapScene(this, map);
    ui->graphicsView->setScene(mapScene);
    connect(mapScene, SIGNAL(selectedTower(Tower *)), this,
            SLOT(onOpenTowerInspector(Tower *)));
    connect(map.get(), SIGNAL(cashChanged(int)), this, SLOT(onCashChange(int)));
  }
}

void TdMap::on_actionLoad_Map_triggered() {
  QString name = QFileDialog::getOpenFileName(this, "Open Map");
  QFile mapFile(name);
  if (!mapFile.open(QIODevice::ReadOnly | QIODevice::Text))
    return;
  QTextStream in(&mapFile);
  map = make_shared<TowerDefense::Map>(in);
  mapScene = new MapScene(this, map);
  ui->graphicsView->setScene(mapScene);
  connect(mapScene, SIGNAL(selectedTower(Tower *)), this,
          SLOT(onOpenTowerInspector(Tower *)));
  connect(map.get(), SIGNAL(cashChanged(int)), this, SLOT(onCashChange(int)));
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
    mapScene->setState(MapUiState::DEFAULT);
  else
    mapScene->setState(MapUiState::DRAW_MAP);
}

void TdMap::on_actionSet_Entrance_triggered() {
  mapScene->setState(MapUiState::SET_ENTRANCE);
}

void TdMap::on_actionSet_Exit_triggered() {
  mapScene->setState(MapUiState::SET_EXIT);
}

void TdMap::onOpenTowerInspector(Tower *tower) {
  auto dialog = new TowerInspectorDialog(this, map.get(), tower);
  dialog->show();
  dialog->raise();
  dialog->activateWindow();
}

void TdMap::onCashChange(int cash)
{
  ui->statusBar->showMessage(QString("Current cash: %1").arg(cash), 2000);
}
