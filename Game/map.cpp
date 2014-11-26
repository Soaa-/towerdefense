#include "map.h"

namespace TowerDefense {

CellType &Map::getCell(Coordinate coord) const {
  return grid[coord.y][coord.x];
}

void Map::createCell(int x, int y) { grid[y][x] = CellType::SCENERY; }

void Map::generatePath() {
  // sanity check
  if (!isValid())
    return;
  if (entrance == exit)
    return false;

  // first coord is entrance
  path.push_back(entrance);

  // keep pushing next path cell into path
  Coordinate *cur = &entrance;
  Coordinate *next = getNext(cur);
  while (*next != exit) {
    if (!next) // sanity check
      return false;
    path.push_back(*next); // push

    // advance cursor
    auto newCur = next;
    next = getNext(next, cur);
    cur = newCur;
  }

  // finally push exit
  path.push_back(exit);
  return true;
}

int Map::getNumPathNeighbors(Coordinate coord) const {
  int x = coord.x;
  int y = coord.y;
  int numNeighbors = 0;

  try {
    if (grid.at(y - 1).at(x) == CellType::PATH)
      ++numNeighbors;
  } catch (std::out_of_range e) {
  }
  try {
    if (grid.at(y + 1).at(x) == CellType::PATH)
      ++numNeighbors;
  } catch (std::out_of_range e) {
  }
  try {
    if (grid.at(y).at(x - 1) == CellType::PATH)
      ++numNeighbors;
  } catch (std::out_of_range e) {
  }
  try {
    if (grid.at(y).at(x + 1) == CellType::PATH)
      ++numNeighbors;
  } catch (std::out_of_range e) {
  }

  return numNeighbors;
}

Coordinate *Map::getNext(Coordinate *coord) const {
  return getNext(coord, nullptr);
}

Coordinate *Map::getNext(Coordinate *coord, Coordinate *prev) const {
  int x = coord->x;
  int y = coord->y;
  int expectedNumPathNeighbors; // 1 if entrance or exit, 2 otherwise
  if (prev)
    expectedNumPathNeighbors = 2;
  else
    expectedNumPathNeighbors = 1;

  if (getNumPathNeighbors(coord) != expectedNumPathNeighbors)
    return nullptr;
  try {
    Coordinate next(x, y - 1);
    if (getCellType(next) == CellType::PATH && next != *prev)
      return next;
  } catch (std::out_of_range) {
  }
  try {
    Coordinate next(x, y + 1);
    if (getCellType(next) == CellType::PATH && next != *prev)
      return next;
  } catch (std::out_of_range) {
  }
  try {
    Coordinate next(x - 1, y);
    if (getCellType(next) == CellType::PATH && next != *prev)
      return next;
  } catch (std::out_of_range) {
  }
  try {
    Coordinate next(x + 1, y);
    if (getCellType(next) == CellType::PATH && next != *prev)
      return next;
  } catch (std::out_of_range) {
  }
  return nullptr;
}

Map::Map(int sizeX, int sizeY)
    : exit(0, 0), entrance(0, 0),
      grid(sizeY, vector<CellType>(sizeX, CellType::SCENERY)) {}

Map::Map(QTextStream &in) : exit(0, 0), entrance(0, 0) {
  QString size = in.readLine();
  int sizeX = size.split(" ")[0].toInt();
  int sizeY = size.split(" ")[1].toInt();
  grid = vector<vector<CellType>>(sizeY, vector<CellType>(sizeX));
  for (int y = 0; y < sizeY; ++y) {
    QString line = in.readLine();
    if (!line.isEmpty())
      for (int x = 0; x < sizeX; ++x) {
        if (line.split(" ").at(x) == "S")
          grid[y][x] = CellType::SCENERY;
        else {
          grid[y][x] = CellType::PATH;
          if (line.split(" ").at(x) == "N")
            entrance = Coordinate(x, y);
          else if (line.split(" ").at(x) == "X")
            exit = Coordinate(x, y);
        }
      }
  }
}

int Map::getSizeX() const { return grid[0].size(); }

int Map::getSizeY() const { return grid.size(); }

CellType Map::getCellType(int x, int y) const { return grid[y][x]; }

CellType Map::getCellType(Coordinate coord) const {
  return getCellType(coord.x, coord.y);
}

void Map::setCellToType(Coordinate coord, CellType type) {
  grid.at(coord.y).at(coord.x) = type;
  emit stateChanged();
}

void Map::setEntrance(Coordinate coord) {
  setCellToType(coord, CellType::PATH);
  entrance = coord;
  emit stateChanged();
}

void Map::setExit(Coordinate coord) {
  setCellToType(coord, CellType::PATH);
  exit = coord;
  emit stateChanged();
}

bool Map::isValid() const {
  // entrance and exit are the same
  if (entrance == exit)
    return false;

  Coordinate *cur = &entrance;
  Coordinate *next = getNext(cur);
  while (*next != exit) {
    if (!next) // no next cell
      return false;

    // advance cursor
    auto newCur = next;
    next = getNext(next, cur);
    cur = newCur;
  }

  return true;
}

bool Map::isEntrance(Coordinate coord) const { return (coord == entrance); }

bool Map::isExit(Coordinate coord) const { return (coord == exit); }

QTextStream &operator<<(QTextStream &stream, const Map &map) {
  stream << map.getSizeX() << " " << map.getSizeY() << "\n";
  for (int y = 0; y < map.getSizeY(); ++y) {
    for (int x = 0; x < map.getSizeX(); ++x) {
      Coordinate coord(x, y);
      if (coord == map.entrance)
        stream << "N ";
      else if (coord == map.exit)
        stream << "X ";
      else if (map.getCellType(coord) == CellType::PATH)
        stream << "P ";
      else
        stream << "S ";
    }
    stream << "\n";
  }
}

} // namespace TowerDefense
