#ifndef FAMILY_HPP
#define FAMILY_HPP

#include <memory>
#include <cmath>
#include <stdexcept>

namespace klyukin
{
  template < class T >
  class Family
  {
  public:
    Family();
    void add(const T& e);
    std::size_t getSize() const noexcept;
    const T& operator[](std::size_t i) const;
    T& operator[](std::size_t i);

  private:
    std::size_t size_;
    std::size_t capacity_;
    std::shared_ptr< T[] > array_;
    Family(const Family& other) = delete;
    Family(Family&& other) = delete;
    Family& operator=(const Family& other) = delete;
    Family& operator=(Family&& other) = delete;
  };

  template < class T >
  Family< T >::Family():
    size_(0),
    capacity_(1),
    array_(new T[1])
  {}

  template < class T >
  void Family< T >::add(const T& e)
  {
    if (size_ == capacity_)
    {
      const double MULT = 1.618;
      std::size_t newCapacity = std::round(capacity_ * MULT);
      std::shared_ptr< T[] > tmp(new T[newCapacity]);
      for (std::size_t i = 0; i < size_; i++)
      {
        tmp[i] = array_[i];
      }
      array_.swap(tmp);
      capacity_ = newCapacity;
    }
    array_[size_] = e;
    size_++;
  }

  template < class T >
  std::size_t Family< T >::getSize() const noexcept
  {
    return size_;
  }

  template < class T >
  const T& Family< T >::operator[](std::size_t i) const
  {
    if (i >= size_)
    {
      throw std::range_error("Family: bad index");
    }
    return array_[i];
  }

  template < class T >
  T& Family< T >::operator[](std::size_t i)
  {
    if (i >= size_)
    {
      throw std::range_error("Family: bad index");
    }
    return array_[i];
  }
}

#endif
