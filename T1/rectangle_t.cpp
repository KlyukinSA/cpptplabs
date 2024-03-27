#include "base-types.hpp"

std::ostream& klyukin::operator<<(std::ostream& stream, rectangle_t r)
{
  return stream << (r.pos.x - r.width / 2) << ' '
                << (r.pos.y - r.height / 2) << ' '
                << (r.pos.x + r.width / 2) << ' '
                << (r.pos.y + r.height / 2);
}
