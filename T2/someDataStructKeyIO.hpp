#ifndef KEY_IO_H
#define KEY_IO_H

#include "DataStruct.hpp"
#include <iosfwd>

namespace klyukin
{
  class KeyIO
  {
  public:
    explicit KeyIO(DataStruct& e);
  private:
    DataStruct& ref_;
    bool haveReadKey_[3];
    friend std::istream& operator>>(std::istream& in, KeyIO& dest);
  };
  std::istream& operator>>(std::istream& in, KeyIO& dest);
}

#endif
