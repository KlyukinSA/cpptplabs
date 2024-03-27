#ifndef REGULAR_HPP
#define REGULAR_HPP

#include "shape.hpp"

namespace klyukin
{
  class Regular: public Shape
  {
  public:
    Regular(point_t v1, point_t v2, point_t v3);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& pos) override;
    void move(double dx, double dy) override;

  private:
    point_t pos_;
    point_t bigRadius_;
    point_t smallRadius_;
    void doScale(double k) override;
    unsigned int getN() const;
    static bool equalsDouble(double d1, double d2);
    static double getVector2DoubleScalarSquare(point_t v);
  };
}

#endif
