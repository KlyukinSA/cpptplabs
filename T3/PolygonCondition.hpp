#ifndef POLYGON_CONDITION_HPP
#define POLYGON_CONDITION_HPP

#include "base-types.hpp"

namespace klyukin
{
  class PolygonCondition
  {
  public:
    enum Mode
    {
      hasEvenVerticesCount = 0,
      hasOddVerticesCount = 1,
      hasNVertices,
      none
    };
    PolygonCondition();
    void setMode(Mode mode);
    Mode getMode() const;
    void setNVertices(std::size_t n);
    bool operator()(const Polygon& p);
  private:
    Mode mode_;
    std::size_t nVertices_;
  };
}

#endif
