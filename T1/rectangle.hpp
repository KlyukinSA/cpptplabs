#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace klyukin
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(point_t v1, point_t v2);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move (const point_t& pos) override;
    void move(double dx, double dy) override;

  private:
    rectangle_t r_;
    void doScale(double k) override;
  };
}

#endif
