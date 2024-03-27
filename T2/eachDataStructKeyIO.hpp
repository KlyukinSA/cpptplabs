#ifndef KEYS_IO_H
#define KEYS_IO_H

#include <iosfwd>
#include <complex>

namespace klyukin
{
  struct LongLongIO
  {
    explicit LongLongIO(long long& e);
    void set(const long long& e);
  private:
    long long& ref_;
  };
  std::istream& operator>>(std::istream& in, LongLongIO&& dest);

  struct ComplexDoubleIO
  {
    explicit ComplexDoubleIO(std::complex< double >& e);
    void set(const std::complex< double >& e);
  private:
    std::complex< double >& ref_;
  };
  std::istream& operator>>(std::istream& in, ComplexDoubleIO&& dest);

  struct StringIO
  {
    explicit StringIO(std::string& e);
    void set(const std::string& e);
  private:
    std::string& ref_;
  };
  std::istream& operator>>(std::istream& in, StringIO&& dest);
}

#endif
