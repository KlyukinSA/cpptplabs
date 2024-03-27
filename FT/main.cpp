#include <iostream>
#include <fstream>
#include "GraphCmdLoop.hpp"

int main(int argc, const char* argv[])
{
  std::ofstream log("input.log");

  if (argc == 2)
  {
    std::ifstream in(argv[1]);
    if (!in)
    {
      std::cerr << "can't open " << argv[1] << '\n';
      return 1;
    }

    klyukin::doGraphCmdLoop(in, std::cout, log, false);

    in.close();
  }
  else
  {
    klyukin::doGraphCmdLoop(std::cin, std::cout, log, true);
  }
  log.close();
  return 0;
}
