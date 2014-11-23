#ifndef COORDINATE_H
#define COORDINATE_H

#include "math.h"

namespace TowerDefense {

struct Coordinate {
  int x;
  int y;

  Coordinate(int x, int y) : x(x), y(y) {}
  Coordinate(const Coordinate &coord) : x(coord.x), y(coord.y) {}

  /**
   * @brief distanceTo Simple triangular distance.
   * @param coord
   * @return
   */
  int distanceTo(const Coordinate &coord) const {
    return (abs(x - coord.x) + abs(y - coord.y));
  }

  bool operator==(const Coordinate &coord) {
    return (x == coord.x && y == coord.y);
  }

  Coordinate operator+(const Coordinate &rhs) {
    Coordinate ret(*this);
    ret.x += rhs.x;
    ret.y += rhs.y;
    return ret;
  }

  Coordinate operator-(const Coordinate &rhs) {
    Coordinate ret(*this);
    ret.x -= rhs.x;
    ret.y -= rhs.y;
    return ret;
  }

  void operator+=(const Coordinate &rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
  }

  void operator-=(const Coordinate &rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;
  }
};

class IHasCoordinate {
public:
  virtual Coordinate getCoord() const = 0;
  virtual int distanceTo(const IHasCoordinate &other) const = 0;
};

class HasCoordinate : public virtual IHasCoordinate {
protected:
  Coordinate coord;

public:
  HasCoordinate(int x, int y) : coord(x, y) {}
  HasCoordinate(const Coordinate &coord) : coord(coord) {}

  virtual Coordinate getCoord() const { return coord; }

  virtual int distanceTo(const IHasCoordinate &other) const {
    return coord.distanceTo(other.getCoord());
  }
};
}

#endif // COORDINATE_H
