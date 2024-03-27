#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include "DataStruct.hpp"

namespace klyukin
{
  void readIteration(std::istream& in, std::vector< klyukin::DataStruct >& v)
  {
    std::copy(
      std::istream_iterator< DataStruct >(in),
      std::istream_iterator< DataStruct >(),
      std::back_inserter(v)
    );
  }
}

int main()
{
  std::vector< klyukin::DataStruct > v;
  readIteration(std::cin, v);
  while (!std::cin.eof())
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    readIteration(std::cin, v);
  }

  std::sort(v.begin(), v.end());

  std::copy(
    std::begin(v),
    std::end(v),
    std::ostream_iterator< klyukin::DataStruct >(std::cout, "\n")
  );
  return 0;
}
