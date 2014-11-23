#ifndef COORDINATE_H
#define COORDINATE_H

namespace TowerDefense {

struct Coordinate {
  int x;
  int y;

  Coordinate(int x, int y) : x(x), y(y) {}
  Coordinate(const Coordinate &coord) : x(coord.x), y(coord.y) {}

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

class HasCoordinate {
protected:
  Coordinate coord;

public:
  HasCoordinate(int x, int y) : coord(x, y) {}
  HasCoordinate(const Coordinate &coord) : coord(coord) {}

  Coordinate getCoord() const { return coord; }
};
}

#endif // COORDINATE_H
