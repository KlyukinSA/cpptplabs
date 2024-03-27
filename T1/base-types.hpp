#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

#include <iostream>

namespace klyukin
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    point_t pos;
    double width;
    double height;
  };

  std::ostream& operator<<(std::ostream& stream, rectangle_t r);
}

#endif
