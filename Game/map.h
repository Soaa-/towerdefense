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

  CellType &getCell(Coordinate coord);

  void createCell(int x, int y);

  int getNumPathNeighbors(Coordinate coord) const;
  unique_ptr<Coordinate> getNext(Coordinate coord) const;
  unique_ptr<Coordinate> getNext(Coordinate coord,
                                 const unique_ptr<Coordinate> &prev) const;

public:
  Map(int sizeX, int sizeY, QObject *parent = 0);
  Map(QTextStream &in, QObject *parent = 0);
  ~Map() {}

  int getSizeX() const;
  int getSizeY() const;
  CellType getCellType(Coordinate coord) const;

  Coordinate getEntrance() const;
  Coordinate getExit() const;
  const vector<Coordinate> &getPath() const;

  bool isValid() const;
  bool isEntrance(Coordinate coord) const;
  bool isExit(Coordinate coord) const;

  vector<vector<CellType>> &getGrid();

  void setCellToType(Coordinate coord, CellType type);
  void setEntrance(Coordinate coord);
  void setExit(Coordinate coord);

  void generatePath();

  friend QTextStream &operator<<(QTextStream &os, const Map &map);

signals:
  void cellTypeChanged(Coordinate coord, CellType type);
  void entranceChanged(Coordinate coord);
  void exitChanged(Coordinate coord);
};

} // namespace TowerDefense

#endif // MAP_H
