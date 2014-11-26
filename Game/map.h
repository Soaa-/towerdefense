#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QTextStream>
#include <vector>
#include <memory>
#include <coordinate.h>

namespace TowerDefense {

using std::vector;
using std::unique_ptr;
using std::make_shared;

enum class CellType { SCENERY, PATH };

class Map : public QObject {
  Q_OBJECT
private:
  Coordinate exit;
  Coordinate entrance;
  vector<vector<CellType>> grid;
  vector<Coordinate> path;

  CellType &getCell(Coordinate coord) const;

  void createCell(int x, int y);

  /**
   * @brief Map::generatePath
   * @return True if path successfully generated, false otherwise.
   */
  void generatePath();

  int getNumPathNeighbors(Coordinate coord) const;
  Coordinate *getNext(Coordinate *coord) const;
  Coordinate *getNext(Coordinate *coord, Coordinate *prev) const;

public:
  Map(int sizeX, int sizeY);
  Map(QTextStream &in);
  int getSizeX() const;
  int getSizeY() const;
  CellType getCellType(Coordinate coord) const;

  bool isValid() const;
  bool isEntrance(Coordinate coord) const;
  bool isExit(Coordinate coord) const;

  vector<vector<CellType>> &getGrid();

  void setCellToType(Coordinate coord, CellType type);
  void setEntrance(Coordinate coord);
  void setExit(Coordinate coord);

  friend QTextStream &operator<<(QTextStream &os, const Map &map);

signals:
  void entranceChanged(Coordinate coord);
  void exitChanged(Coordinate coord);
};

} // namespace TowerDefense

#endif // MAP_H
