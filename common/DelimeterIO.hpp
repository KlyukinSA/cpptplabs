#ifndef DELIMETER_IO_H
#define DELIMETER_IO_H

#include <iosfwd>

namespace klyukin
{
  struct DelimeterIO
  {
    explicit DelimeterIO(const char& e);
    char get();
  private:
    char exp_;
  };
  std::istream& operator>>(std::istream& in, DelimeterIO&& dest);
}

#endif
