#include "eachDataStructKeyIO.hpp"
#include <istream>
#include "DelimeterIO.hpp"
#include "MultipleIO.hpp"

std::istream& klyukin::operator>>(std::istream& in, LongLongIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  long long l;
  MultipleIO< char > mc(0);
  in >> l >> mc >> mc;
  dest.set(l);
  if (mc.getItem() != 'l' && mc.getItem() != 'L')
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& klyukin::operator>>(std::istream& in, ComplexDoubleIO&& dest)
{
  double re, im;
  in >> DelimeterIO{'#'} >> DelimeterIO{'c'} >> DelimeterIO{'('}
     >> re >> im >> DelimeterIO{')'};
  dest.set(std::complex< double >{re, im});
  return in;
}

std::istream& klyukin::operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::string str;
  std::getline(in >> DelimeterIO{'"'}, str, '"');
  dest.set(str);
  return in;
}

klyukin::LongLongIO::LongLongIO(long long& e):
  ref_(e)
{}
void klyukin::LongLongIO::set(const long long& e)
{
  ref_ = e;
}
klyukin::ComplexDoubleIO::ComplexDoubleIO(std::complex< double >& e):
  ref_(e)
{}
void klyukin::ComplexDoubleIO::set(const std::complex< double >& e)
{
  ref_ = e;
}
klyukin::StringIO::StringIO(std::string& e):
  ref_(e)
{}
void klyukin::StringIO::set(const std::string& e)
{
  ref_ = e;
}
