#include "regular.hpp"
#include <cmath>
#include <stdexcept>
#include <limits>

klyukin::Regular::Regular(point_t v1, point_t v2, point_t v3):
  pos_(v1),
  bigRadius_({0, 0}),
  smallRadius_({0, 0})
{
  double a = getVector2DoubleScalarSquare({v1.x - v2.x, v1.y - v2.y});
  double b = getVector2DoubleScalarSquare({v2.x - v3.x, v2.y - v3.y});
  double c = getVector2DoubleScalarSquare({v3.x - v1.x, v3.y - v1.y});
  if (equalsDouble(a, c + b))
  {
    bigRadius_ = {v2.x - v1.x, v2.y - v1.y};
    smallRadius_ = {v3.x - v1.x, v3.y - v1.y};
  }
  else if (equalsDouble(c, a + b))
  {
    bigRadius_ = {v3.x - v1.x, v3.y - v1.y};
    smallRadius_ = {v2.x - v1.x, v2.y - v1.y};
  }
  else
  {
    throw std::range_error("bad triangle for regular");
  }
  double alpha = std::acos(std::sqrt(
    getVector2DoubleScalarSquare(smallRadius_) /
        getVector2DoubleScalarSquare(bigRadius_)));
  double tmp = std::acos(-1) / alpha;
  unsigned int n = std::round(tmp);
  if (!equalsDouble(n, tmp))
  {
    throw std::range_error("bad triangle for regular");
  }
}

double klyukin::Regular::getArea() const
{
  double small = getVector2DoubleScalarSquare(smallRadius_);
  double big = getVector2DoubleScalarSquare(bigRadius_);
  return getN() * std::sqrt(small * (big - small));
}

klyukin::rectangle_t klyukin::Regular::getFrameRect() const
{
  point_t bigRadius = bigRadius_;
  point_t smallRadius = smallRadius_;
  double k = 2 * getVector2DoubleScalarSquare(smallRadius_) /
      getVector2DoubleScalarSquare(bigRadius_);
  double maxX, minX, maxY, minY;
  maxX = minX = pos_.x + bigRadius_.x;
  maxY = minY = pos_.y + bigRadius_.y;
  const int reserve = 2;
  int n = getN();
  for (int i = 0; i <= n + reserve; i++)
  {
    if (pos_.x + bigRadius.x > maxX)
    {
      maxX = pos_.x + bigRadius.x;
    }
    if (pos_.y + bigRadius.y > maxY)
    {
      maxY = pos_.y + bigRadius.y;
    }
    if (pos_.x + bigRadius.x < minX)
    {
      minX = pos_.x + bigRadius.x;
    }
    if (pos_.y + bigRadius.y < minY)
    {
      minY = pos_.y + bigRadius.y;
    }
    smallRadius.x = k * bigRadius.x - smallRadius.x;
    smallRadius.y = k * bigRadius.y - smallRadius.y;
    bigRadius.x = 2 * smallRadius.x - bigRadius.x;
    bigRadius.y = 2 * smallRadius.y - bigRadius.y;
  }
  return {{(maxX + minX) / 2, (maxY + minY) / 2}, maxX - minX, maxY - minY};
}

void klyukin::Regular::move(const point_t& pos)
{
  pos_ = pos;
}

void klyukin::Regular::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void klyukin::Regular::doScale(double k)
{
  bigRadius_.x *= k;
  bigRadius_.y *= k;
  smallRadius_.x *= k;
  smallRadius_.y *= k;
}

unsigned int klyukin::Regular::getN() const
{
  double alpha = std::acos(std::sqrt(
    getVector2DoubleScalarSquare(smallRadius_) /
        getVector2DoubleScalarSquare(bigRadius_)));
  double tmp = std::acos(-1) / alpha;
  return std::round(tmp);
}

bool klyukin::Regular::equalsDouble(double d1, double d2)
{
  return std::fabs(d1 - d2) < std::numeric_limits< double >::epsilon();
}

double klyukin::Regular::getVector2DoubleScalarSquare(point_t v)
{
  return v.x * v.x + v.y * v.y;
}
