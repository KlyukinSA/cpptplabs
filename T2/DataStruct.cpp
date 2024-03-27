#include "DataStruct.hpp"
#include <iostream>
#include <iomanip>
#include "someDataStructKeyIO.hpp"
#include "DelimeterIO.hpp"
#include "iofmtguard.hpp"

bool klyukin::DataStruct::operator<(const DataStruct& other)
{
  if (key1 == other.key1)
  {
    if (key2 == other.key2)
    {
      return key3.size() < other.key3.size();
    }
    return std::norm(key2) < std::norm(other.key2);
  }
  return key1 < other.key1;
}

std::istream& klyukin::operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  KeyIO k(dest);
  return in >> DelimeterIO{'('} >> k >> k >> k >> DelimeterIO{':'} >> DelimeterIO{')'};
}

std::ostream& klyukin::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  return out << std::setprecision(1) << std::fixed
             << "(:key1 " << data.key1
             << "ll:key2 #c(" << data.key2.real() << ' ' << data.key2.imag()
             << "):key3 \"" << data.key3 << "\":)";
}
