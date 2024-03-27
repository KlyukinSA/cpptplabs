#ifndef ADD_POLYGON_AREA_IF_HPP
#define ADD_POLYGON_AREA_IF_HPP

#include "PolygonCondition.hpp"

namespace klyukin
{
  class AddPolygonAreaIf
  {
  public:
    AddPolygonAreaIf(const PolygonCondition& cond);
    double operator()(double s, const Polygon& p);
  private:
    PolygonCondition condition_;
  };
}

#endif
