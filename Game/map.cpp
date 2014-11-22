#include "map.h"

namespace TowerDefense {

void Map::createCell(int x, int y) {
  grid[y][x] = make_shared<Cell>(x, y);
  connect(grid[y][x].get(), SIGNAL(contentChanged()), this,
          SIGNAL(stateChanged()));
}

int Map::getNumPathNeighbors(shared_ptr<Cell> cell) const {
  return getNumPathNeighbors(cell->getX(), cell->getY());
}

int Map::getNumPathNeighbors(int x, int y) const {
  int numNeighbors = 0;

  try {
    if (grid.at(y - 1).at(x)->getType() == CellType::PATH)
      ++numNeighbors;
  } catch (std::out_of_range e) {
  }
  try {
    if (grid.at(y + 1).at(x)->getType() == CellType::PATH)
      ++numNeighbors;
  } catch (std::out_of_range e) {
  }
  try {
    if (grid.at(y).at(x - 1)->getType() == CellType::PATH)
      ++numNeighbors;
  } catch (std::out_of_range e) {
  }
  try {
    if (grid.at(y).at(x + 1)->getType() == CellType::PATH)
      ++numNeighbors;
  } catch (std::out_of_range e) {
  }

  return numNeighbors;
}

shared_ptr<Cell> Map::getNext(shared_ptr<Cell> cell) const {
  return getNext(cell, shared_ptr<Cell>(nullptr));
}

shared_ptr<Cell> Map::getNext(shared_ptr<Cell> cell,
                              shared_ptr<Cell> prev) const {
  int x = cell->getX();
  int y = cell->getY();
  int expectedNumPathNeighbors; // 1 if entrance or exit, 2 otherwise
  if (prev.get())
    expectedNumPathNeighbors = 2;
  else
    expectedNumPathNeighbors = 1;

  if (getNumPathNeighbors(x, y) != expectedNumPathNeighbors)
    return shared_ptr<Cell>(nullptr);
  try {
    auto next = grid.at(y - 1).at(x);
    if (next->getType() == CellType::PATH && next != prev)
      return next;
  } catch (std::out_of_range) {
  }
  try {
    auto next = grid.at(y + 1).at(x);
    if (next->getType() == CellType::PATH && next != prev)
      return next;
  } catch (std::out_of_range) {
  }
  try {
    auto next = grid.at(y).at(x - 1);
    if (next->getType() == CellType::PATH && next != prev)
      return next;
  } catch (std::out_of_range) {
  }
  try {
    auto next = grid.at(y).at(x + 1);
    if (next->getType() == CellType::PATH && next != prev)
      return next;
  } catch (std::out_of_range) {
  }
  return shared_ptr<Cell>(nullptr);
}

Map::Map(int sizeX, int sizeY)
    : exit(nullptr), entrance(nullptr),
      grid(sizeY, vector<shared_ptr<Cell>>(sizeX)) {
  for (int y = 0; y < sizeY; ++y) {
    for (int x = 0; x < sizeX; ++x) {
      createCell(x, y);
    }
  }
}

Map::Map(QTextStream &in) : exit(nullptr), entrance(nullptr) {
  QString size = in.readLine();
  int sizeX = size.split(" ")[0].toInt();
  int sizeY = size.split(" ")[1].toInt();
  grid =
      vector<vector<shared_ptr<Cell>>>(sizeY, vector<shared_ptr<Cell>>(sizeX));
  for (int y = 0; y < sizeY; ++y) {
    QString line = in.readLine();
    if (!line.isEmpty())
      for (int x = 0; x < sizeX; ++x) {
        createCell(x, y);
        if (line.split(" ").at(x) == "S")
          grid[y][x]->setCellToType(CellType::SCENERY);
        else {
          grid[y][x]->setCellToType(CellType::PATH);
          if (line.split(" ").at(x) == "N")
            entrance = grid[y][x];
          else if (line.split(" ").at(x) == "X")
            exit = grid[y][x];
        }
      }
  }
}

int Map::getSizeX() const { return grid[0].size(); }

int Map::getSizeY() const { return grid.size(); }

shared_ptr<Cell> Map::getCell(int x, int y) const {
  return shared_ptr<Cell>(grid[y][x]);
}

CellType Map::getCellType(int x, int y) const { return grid[y][x]->getType(); }

void Map::setCellToType(int x, int y, CellType type) {
  grid.at(y).at(x)->setCellToType(type);
}

void Map::setEntrance(int x, int y) {
  setCellToType(x, y, CellType::PATH);
  entrance = getCell(x, y);
  emit stateChanged();
}

void Map::setExit(int x, int y) {
  setCellToType(x, y, CellType::PATH);
  exit = getCell(x, y);
  emit stateChanged();
}

void Map::onTowerLevelChanged(int, int cost)
{

}

bool Map::isValid() const {
  // make sure coordinates are set properly
  for (int y = 0; y < getSizeY(); ++y) {
    for (int x = 0; x < getSizeX(); ++x) {
      auto cell = grid[y][x];
      if (cell->getX() != x || cell->getY() != y)
        return false;
    }
  }

  // if no entrance nor exit, map is invalid
  if (!entrance || !exit)
    return false;

  // check path
  auto prev = entrance;
  auto temp = entrance;
  auto current = getNext(entrance);

  // no valid path past entrance
  if (!current)
    return false;

  // if we trace all the way to the exit, then the path is valid
  while (current != exit) {
    temp = current;
    current = getNext(current, prev);
    if (!current.get())
      return false;
    prev = temp;
  }

  return true;
}

bool Map::isEntrance(int x, int y) const { return (getCell(x, y) == entrance); }

bool Map::isExit(int x, int y) const { return (getCell(x, y) == exit); }

void Map::placeTower(int x, int y, Tower *tower) {
  auto cell = getCell(x, y);
  if (cell->getTower())
    return;
  auto price = tower->getPurchasePrice();
  if (price > cash)
    return;
  cell->placeTower(tower);
  cash -= price;
  emit cashChanged(cash);
}

void Map::upgradeTower(int x, int y) {
  auto tower = getCell(x, y)->getTower();
  auto price = tower->getUpgradePrice();
  if (price > cash)
    return;
  tower->upgrade();
}

QTextStream &operator<<(QTextStream &stream, const Map &map) {
  stream << map.getSizeX() << " " << map.getSizeY() << "\n";
  for (auto row : map.grid) {
    for (auto cell : row) {
      if (cell == map.entrance)
        stream << "N ";
      else if (cell == map.exit)
        stream << "X ";
      else if (cell->getType() == CellType::PATH)
        stream << "P ";
      else
        stream << "S ";
    }
    stream << "\n";
  }
  return stream;
}

} // namespace TowerDefense
