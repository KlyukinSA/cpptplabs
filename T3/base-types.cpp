#include "base-types.hpp"
#include <iostream>
#include <iterator>
#include <limits>
#include "DelimeterIO.hpp"

std::istream& klyukin::operator>>(std::istream& in, Point& dest)
{
  return in >> DelimeterIO{'('} >> dest.x >> DelimeterIO{';'} >> dest.y >> DelimeterIO{')'};
}

std::istream& klyukin::operator>>(std::istream& in, Polygon& dest)
{
  Polygon res;
  std::size_t count = 0;
  in >> count;
  const std::size_t MINIMAL_POLYGON_POINTS_COUNT = 3;
  if (count < MINIMAL_POLYGON_POINTS_COUNT)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::streampos start = in.tellg();
  std::copy(
    std::istream_iterator< Point >(in),
    std::istream_iterator< Point >(),
    std::back_inserter(res.points)
  );

  in.clear();
  in.seekg(start);
  if (res.points.size() == count)
  {
    dest = res;
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

double klyukin::Polygon::getArea() const
{
  long long s = 0;
  std::size_t size = points.size();
  for (std::size_t i = 0; i < size; i++)
  {
    s += points[i].x * points[(i + 1) % size].y - points[(i + 1) % size].x * points[i].y;
  }
  return std::abs(s) / 2.0;
}

bool klyukin::Polygon::makesRightAngle(Point p1, Point p2, Point p3)
{
  return !((p1.x - p2.x) * (p2.x - p3.x) + (p1.y - p2.y) * (p2.y - p3.y));
}

bool klyukin::Polygon::hasRightAngle() const
{
  std::size_t size = points.size();
  for (std::size_t i = 0; i < size; i++)
  {
    if (makesRightAngle(points[i], points[(i + 1) % size], points[(i + 2) % size]))
    {
      return true;
    }
  }
  return false;
}

bool klyukin::Polygon::isRectangle() const
{
  const std::size_t N_RECTANGLE_VERTICES = 4;
  if (points.size() != N_RECTANGLE_VERTICES)
  {
    return false;
  }
  const std::size_t N_RECTANGLE_ANGLES = N_RECTANGLE_VERTICES;
  for (std::size_t i = 0; i < N_RECTANGLE_ANGLES; i++)
  {
    if (!makesRightAngle(points[i],
      points[(i + 1) % N_RECTANGLE_ANGLES], points[(i + 2) % N_RECTANGLE_ANGLES]))
    {
      return false;
    }
  }
  return true;
}
