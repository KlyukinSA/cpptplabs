#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <iterator>
#include <limits>
#include <numeric>
#include <exception>
#include <functional>
#include <string>
#include <algorithm>
#include <map>
#include "base-types.hpp"
#include "PolygonCondition.hpp"
#include "AddPolygonAreaIf.hpp"
#include "Commands.hpp"

namespace klyukin
{
  static void readIteration(std::istream& in, std::vector< Polygon >& v)
  {
    std::copy(
      std::istream_iterator< Polygon >(in),
      std::istream_iterator< Polygon >(),
      std::back_inserter(v)
    );
  }

  static void printErrorMessage(std::ostream& out)
  {
    out << "<INVALID COMMAND>\n";
  }
}

int main(int argc, const char* argv[])
{
  if (argc < 2)
  {
    std::cerr << "no input file name\n";
    return 1;
  }
  std::ifstream in(argv[1]);
  if (!in)
  {
    std::cerr << "cant open " << argv[1] << '\n';
    return 1;
  }
  std::vector< klyukin::Polygon > v;
  klyukin::readIteration(in, v);
  while (!in.eof())
  {
    in.clear();
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    klyukin::readIteration(in, v);
  }
  in.close();

  std::cout << std::setprecision(1) << std::fixed;
  klyukin::Commands commands(v, std::cin, std::cout);
  std::map< std::string, std::function< void() > > commandsMap =
  {
    {"COUNT", std::bind(&klyukin::Commands::doCount, std::ref(commands))},
    {"AREA", std::bind(&klyukin::Commands::doArea, std::ref(commands))},
    {"MAX", std::bind(&klyukin::Commands::doMax, std::ref(commands))},
    {"MIN", std::bind(&klyukin::Commands::doMin, std::ref(commands))},
    {"RECTS", std::bind(&klyukin::Commands::doRects, std::ref(commands))},
    {"RIGHTSHAPES", std::bind(&klyukin::Commands::doRightShapes, std::ref(commands))}
  };
  std::string str;
  std::cin >> str;
  while (!std::cin.eof())
  {
    try
    {
      if (commandsMap.find(str) != commandsMap.end())
      {
        commandsMap.find(str)->second();
      }
      else
      {
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        throw std::logic_error("unknown command");
      }
    }
    catch(const std::logic_error&)
    {
      klyukin::printErrorMessage(std::cout);
    }
    std::cin >> str;
  }
  return 0;
}
