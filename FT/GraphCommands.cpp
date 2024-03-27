#include "GraphCommands.hpp"
#include <iostream>
#include <string>

klyukin::GraphCommands::GraphCommands(std::istream& in, std::ostream& out, std::ostream& log):
  g_(new Graph(1)),
  in_(in),
  out_(out),
  log_(log)
{}

void klyukin::GraphCommands::doCreate()
{
  std::size_t size;
  in_ >> size;
  log_ << ' ' << size;
  if (in_)
  {
    g_ = std::make_shared< Graph >(size);
  }
  else
  {
    out_ << "give size\n";
    in_.clear();
  }
}

void klyukin::GraphCommands::doHasVertices()
{
  out_ << "graph has ";
  if (!g_->hasVertices())
  {
    out_ << "no ";
  }
  out_ << "vertices\n";
}

void klyukin::GraphCommands::doHasVertex()
{
  std::size_t v;
  in_ >> v;
  log_ << ' ' << v;
  if (in_)
  {
    out_ << "graph has ";
    if (!g_->hasVertex(v))
    {
      out_ << "not ";
    }
    out_ << "this vertex\n";
  }
  else
  {
    out_ << "give vertex\n";
    in_.clear();
  }
}

void klyukin::GraphCommands::doHasEdge()
{
  std::size_t x, y;
  in_ >> x >> y;
  log_ << ' ' << x << ' ' << y;
  if (in_)
  {
    out_ << "graph has ";
    if (!g_->hasEdge(x, y))
    {
      out_ << "not ";
    }
    out_ << "this edge\n";
  }
  else
  {
    out_ << "give 2 vertices\n";
    in_.clear();
  }
}

void klyukin::GraphCommands::doAddVertex()
{
  std::vector< std::size_t > adjacentVertices;
  std::string line;
  std::getline(in_, line);
  log_ << line;
  if (line.size() >= 2)
  {
    std::size_t pos1 = 1;
    std::size_t pos2 = line.find(' ', pos1);
    while (pos1 != std::string::npos && pos2 > pos1)
    {
      adjacentVertices.push_back(std::stoi(
        line.substr(pos1, pos2 - pos1))
      );
      pos1 = pos2 + 1;
      pos2 = line.find(' ', pos1);
    }
  }
  out_ << "added vertex #" << g_->addVertex(adjacentVertices) << '\n';
}

void klyukin::GraphCommands::doRemoveVertex()
{
  std::size_t v;
  in_ >> v;
  log_ << ' ' << v;
  if (in_)
  {
    if (!g_->removeVertex(v))
    {
      out_ << "cant remove\n";
    }
  }
  else
  {
    out_ << "give vertex\n";
    in_.clear();
  }
}

void klyukin::GraphCommands::doBreadthFirstSearch()
{
  std::size_t start;
  in_ >> start;
  log_ << ' ' << start;
  if (in_)
  {
    g_->breadthFirstSearch(start, &out_,
      [] (void* out, std::size_t x, std::size_t y)
      {
        *(std::ostream*)(out) << "go from " << x << " to " << y << '\n';
      }
    );
  }
  else
  {
    out_ << "give start\n";
    in_.clear();
  }
}

void klyukin::GraphCommands::doGetPath()
{
  std::size_t start;
  in_ >> start;
  log_ << ' ' << start;
  if (in_)
  {
    g_->getPath(start, out_);
  }
  else
  {
    out_ << "give start\n";
    in_.clear();
  }
}

void klyukin::GraphCommands::doGetDiameter()
{
  std::size_t start;
  in_ >> start;
  log_ << ' ' << start;
  if (in_)
  {
    out_ << "diameter = " << g_->getDiameter(start) << '\n';
  }
  else
  {
    out_ << "give start\n";
    in_.clear();
  }
}
