#include "AddPolygonAreaIf.hpp"

klyukin::AddPolygonAreaIf::AddPolygonAreaIf(const PolygonCondition& cond):
  condition_(cond)
{}

double klyukin::AddPolygonAreaIf::operator()(double s, const Polygon& p)
{
  if (condition_(p))
  {
    return s + p.getArea();
  }
  else
  {
    return s;
  }
}
