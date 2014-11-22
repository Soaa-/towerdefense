#include "cell.h"

namespace TowerDefense {

bool Cell::containsTower()
{
  return tower != nullptr;
}

bool Cell::containsCritterGroup()
{
  return critter != nullptr;
}

void Cell::setCellToType(CellType type) {
  this->type = type;
  switch (type) {
  case CellType::PATH:
    this->critter = nullptr;
    break;
  case CellType::SCENERY:
    this->tower = nullptr;
    break;
  }
  emit contentChanged();
}

void Cell::placeTower(Tower *tower) {
  if (type == CellType::PATH)
    throw std::logic_error("attempted to place tower on path cell");
  this->tower = std::move(unique_ptr<Tower>(tower));
  emit contentChanged();
}

void Cell::placeCritter(Critter *critterGroup) {
  if (type == CellType::PATH)
    throw std::logic_error("attempted to place critter on scenery cell");
  this->critter = std::move(unique_ptr<Critter>(critterGroup));
  emit contentChanged();
}

void Cell::moveCritterFromCell(Cell &cell) {
  if (type == CellType::PATH)
    throw std::logic_error("attempted to move critter on scenery cell");
  this->critter = std::move(cell.critter);
  emit contentChanged();
  emit cell.contentChanged();
}

}
