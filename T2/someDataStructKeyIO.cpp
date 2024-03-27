#include "someDataStructKeyIO.hpp"
#include <istream>
#include "eachDataStructKeyIO.hpp"
#include "DelimeterIO.hpp"

klyukin::KeyIO::KeyIO(DataStruct& e):
  ref_(e),
  haveReadKey_{false, false, false}
{}
std::istream& klyukin::operator>>(std::istream& in, KeyIO& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimeterIO{':'};
  std::string str;
  in >> str;
  if (str == "key1")
  {
    if (dest.haveReadKey_[0])
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> LongLongIO{dest.ref_.key1};
    dest.haveReadKey_[0] = true;
  }
  else if (str == "key2")
  {
    if (dest.haveReadKey_[1])
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> ComplexDoubleIO{dest.ref_.key2};
    dest.haveReadKey_[1] = true;
  }
  else if (str == "key3")
  {
    if (dest.haveReadKey_[2])
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> StringIO{dest.ref_.key3};
    dest.haveReadKey_[2] = true;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
