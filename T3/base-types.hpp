#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

#include <vector>
#include <iosfwd>

namespace klyukin
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
    double getArea() const;
    bool hasRightAngle() const;
    bool isRectangle() const;
  private:
    static bool makesRightAngle(Point p1, Point p2, Point p3);
  };
  std::istream& operator>>(std::istream& in, Point& dest);
  std::istream& operator>>(std::istream& in, Polygon& dest);
}

#endif
