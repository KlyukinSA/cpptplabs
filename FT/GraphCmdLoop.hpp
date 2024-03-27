#ifndef GRAPH_CMD_LOOP_HPP
#define GRAPH_CMD_LOOP_HPP

#include <iosfwd>

namespace klyukin
{
  void doGraphCmdLoop(std::istream& in, std::ostream& out, std::ostream& log, bool invite = true);
}

#endif
