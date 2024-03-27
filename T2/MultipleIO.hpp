#ifndef MULTIPLE_IO_H
#define MULTIPLE_IO_H

#include <iostream>

namespace klyukin
{
  template < class T >
  class MultipleIO
  {
  public:
    explicit MultipleIO(const T& e);
    T getItem();
  private:
    T item_;
    bool isSet_;
    template < class T1 >
    friend std::istream& operator>>(std::istream& in, MultipleIO< T1 >& dest);
  };
  template < class T >
  MultipleIO< T >::MultipleIO(const T& e):
    item_(e),
    isSet_(false)
  {}
  template < class T >
  T MultipleIO< T >::getItem()
  {
    return item_;
  }
  template < class T >
  std::istream& operator>>(std::istream& in, MultipleIO< T >& dest)
  {
    T tmp;
    in >> tmp;
    if (dest.isSet_)
    {
      if (dest.item_ != tmp)
      {
        in.setstate(std::ios::failbit);
      }
    }
    else
    {
      if (in)
      {
        dest.item_ = tmp;
        dest.isSet_ = true;
      }
    }
    return in;
  }
}

#endif
