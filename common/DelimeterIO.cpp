#include "DelimeterIO.hpp"
#include <istream>

std::istream& klyukin::operator>>(std::istream& in, DelimeterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.get()))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

klyukin::DelimeterIO::DelimeterIO(const char& e):
  exp_(e)
{}
char klyukin::DelimeterIO::get()
{
  return exp_;
}
