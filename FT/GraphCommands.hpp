#ifndef GRAPH_COMMANDS_HPP
#define GRAPH_COMMANDS_HPP

#include <iosfwd>
#include <memory>
#include "Graph.hpp"

namespace klyukin
{
  class GraphCommands
  {
    public:
      GraphCommands(std::istream& in, std::ostream& out, std::ostream& log);
      void doCreate();
      void doHasVertices();
      void doHasVertex();
      void doHasEdge();
      void doAddVertex();
      void doRemoveVertex();
      void doBreadthFirstSearch();
      void doGetPath();
      void doGetDiameter();

    private:
      std::shared_ptr< Graph > g_;
      std::istream& in_;
      std::ostream& out_;
      std::ostream& log_;
  };
}

#endif
