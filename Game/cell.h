#ifndef CELL_H
#define CELL_H

#include <QObject>
#include <memory>
#include "Game/tower.h"
#include "Game/critter.h"

namespace TowerDefense {

using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;

enum class CellType { SCENERY, PATH };

class Cell : public QObject {
  Q_OBJECT
private:
  size_t x;
  size_t y;

  CellType type;
  unique_ptr<Tower> tower;
  unique_ptr<Critter> critter;

  Cell() {}

public:
  Cell(int x, int y, CellType type)
      : x(x), y(y), type(type), tower(nullptr), critter(nullptr) {}

  Cell(int x, int y) : Cell(x, y, CellType::SCENERY) {}

  std::size_t getX() const { return x; }
  std::size_t getY() const { return y; }

  CellType getType() const { return type; }
  Tower *getTower() { return tower.get(); }
  Critter *getCritter() { return critter.get(); }

  bool containsTower();
  bool containsCritterGroup();

  void setCellToType(CellType type);
  void placeTower(Tower *tower);
  void placeCritter(Critter *critter);
  void moveCritterFromCell(Cell &cell);

signals:
  void contentChanged();
};

} // namespace TowerDefense

#endif // CELL_H
