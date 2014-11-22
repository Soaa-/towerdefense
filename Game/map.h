#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QTextStream>
#include <vector>
#include <memory>
#include <Game/cell.h>

namespace TowerDefense {

using std::vector;
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;
using std::dynamic_pointer_cast;

class Map : public QObject {
  Q_OBJECT
private:
  shared_ptr<Cell> exit;
  shared_ptr<Cell> entrance;
  vector<vector<shared_ptr<Cell>>> grid;

  int cash = 500;

  void createCell(int x, int y);

  int getNumPathNeighbors(shared_ptr<Cell> cell) const;
  int getNumPathNeighbors(int x, int y) const;

  shared_ptr<Cell> getNext(shared_ptr<Cell> cell) const;
  shared_ptr<Cell> getNext(shared_ptr<Cell> cell,
                           shared_ptr<Cell> prev) const;

public:
  Map(int sizeX, int sizeY);
  Map(QTextStream &in);
  int getSizeX() const;
  int getSizeY() const;
  shared_ptr<Cell> getCell(int x, int y) const;
  CellType getCellType(int x, int y) const;
  bool isValid() const;
  bool isEntrance(int x, int y) const;
  bool isExit(int x, int y) const;

  bool deductCash(int amount) {
    if (amount > cash)
      return false;
    cash -= amount;
    emit cashChanged(cash);
    return true;
  }

  void placeTower(int x, int y, Tower *tower);
  void upgradeTower(int x, int y);
  void setCellToType(int x, int y, CellType type);
  void setEntrance(int x, int y);
  void setExit(int x, int y);

  friend QTextStream &operator<<(QTextStream& os, const Map& map);

public slots:
  void onTowerLevelChanged(int, int cost);

signals:
  void stateChanged();
  void cashChanged(int newAmount);
};

} // namespace TowerDefense

#endif // MAP_H
