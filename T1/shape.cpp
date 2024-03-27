#include "shape.hpp"
#include <limits>
#include <stdexcept>

void klyukin::Shape::scale(double k)
{
  if (k <= std::numeric_limits< double >::epsilon())
  {
    throw std::range_error("bad scale");
  }
  doScale(k);
}
