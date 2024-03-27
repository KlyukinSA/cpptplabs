#include "circle.hpp"
#include <cmath>
#include <stdexcept>
#include <limits>

klyukin::Circle::Circle(const point_t& pos, double radius):
  pos_(pos),
  radius_(radius)
{
  if (radius <= std::numeric_limits< double >::epsilon())
  {
    throw std::range_error("bad radius");
  }
}

double klyukin::Circle::getArea() const
{
  return std::acos(-1) * radius_ * radius_;
}

klyukin::rectangle_t klyukin::Circle::getFrameRect() const
{
  return {pos_, radius_ * 2, radius_ * 2};
}

void klyukin::Circle::move(const point_t& pos)
{
  pos_ = pos;
}

void klyukin::Circle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void klyukin::Circle::doScale(double k)
{
  radius_ *= k;
}
