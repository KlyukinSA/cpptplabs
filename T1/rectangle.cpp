#include "rectangle.hpp"
#include <stdexcept>
#include <limits>

klyukin::Rectangle::Rectangle(point_t v1, point_t v2):
  r_{{(v1.x + v2.x) / 2, (v1.y + v2.y) / 2}, v2.x - v1.x, v2.y - v1.y}
{
  if (r_.width <= std::numeric_limits< double >::epsilon() ||
      r_.height <= std::numeric_limits< double >::epsilon())
  {
    throw std::range_error("bad width or height");
  }
}

double klyukin::Rectangle::getArea() const
{
  return r_.width * r_.height;
}

klyukin::rectangle_t klyukin::Rectangle::getFrameRect() const
{
  return {r_.pos, r_.width, r_.height};
}

void klyukin::Rectangle::move(const point_t& pos)
{
  r_.pos = pos;
}

void klyukin::Rectangle::move(double dx, double dy)
{
  r_.pos.x += dx;
  r_.pos.y += dy;
}

void klyukin::Rectangle::doScale(double k)
{
  r_.width *= k;
  r_.height *= k;
}
