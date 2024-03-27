#include "PolygonCondition.hpp"

klyukin::PolygonCondition::PolygonCondition():
  mode_(none),
  nVertices_(0)
{}
void klyukin::PolygonCondition::setMode(Mode mode)
{
  mode_ = mode;
}
void klyukin::PolygonCondition::setNVertices(std::size_t n)
{
  nVertices_ = n;
}
klyukin::PolygonCondition::Mode klyukin::PolygonCondition::getMode() const
{
  return mode_;
}

bool klyukin::PolygonCondition::operator()(const Polygon& p)
{
  if (mode_ == none)
  {
    return true;
  }
  else if (mode_ == hasNVertices)
  {
    return p.points.size() == nVertices_;
  }
  else
  {
    return p.points.size() % 2 == mode_;
  }
}
