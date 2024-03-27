#include "GraphCmdLoop.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <functional>
#include <exception>
#include <limits>
#include "GraphCommands.hpp"

void klyukin::doGraphCmdLoop(std::istream& in, std::ostream& out, std::ostream& log, bool invite)
{
  klyukin::GraphCommands commands(in, out, log);
  std::map< std::string, std::function< void() > > commandsMap =
  {
    {"create", std::bind(&klyukin::GraphCommands::doCreate, std::ref(commands))},
    {"has-vertices", std::bind(&klyukin::GraphCommands::doHasVertices, std::ref(commands))},
    {"has-vertex", std::bind(&klyukin::GraphCommands::doHasVertex, std::ref(commands))},
    {"has-edge", std::bind(&klyukin::GraphCommands::doHasEdge, std::ref(commands))},
    {"add-vertex", std::bind(&klyukin::GraphCommands::doAddVertex, std::ref(commands))},
    {"remove-vertex", std::bind(&klyukin::GraphCommands::doRemoveVertex, std::ref(commands))},
    {"breadth-first-search", std::bind(&klyukin::GraphCommands::doBreadthFirstSearch, std::ref(commands))},
    {"get-path", std::bind(&klyukin::GraphCommands::doGetPath, std::ref(commands))},
    {"get-diameter", std::bind(&klyukin::GraphCommands::doGetDiameter, std::ref(commands))}
  };
  std::string str;
  if (invite)
  {
    out << ">>> ";
  }
  in >> str;
  while (!in.eof())
  {
    log << str;
    try
    {
      if (commandsMap.find(str) != commandsMap.end())
      {
        commandsMap.find(str)->second();
      }
      else
      {
        in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        throw std::logic_error("no such command");
      }
    }
    catch(const std::exception& e)
    {
      out << e.what() << '\n';
    }
    log << '\n';
    if (invite)
    {
      out << ">>> ";
    }
    in >> str;
  }
  if (invite)
  {
    out << '\n';
  }
}
