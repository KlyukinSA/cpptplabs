#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <forward_list>
#include <iosfwd>

namespace klyukin
{
  class Graph
  {
  public:
    Graph(std::size_t size);
    bool hasVertex(std::size_t i) const;
    bool hasVertices() const;
    bool hasEdge(std::size_t x, std::size_t y) const;
    std::size_t addVertex(const std::vector< std::size_t >& adjacentVertices);
    bool removeVertex(std::size_t pos);
    void breadthFirstSearch(std::size_t start,
      void* data, void (*processEdge)(void* data, std::size_t x, std::size_t y)) const;
    void getPath(std::size_t start, std::ostream& out) const;
    std::size_t getDiameter(std::size_t start) const;

  private:
    std::size_t capacity_;
    std::vector< std::forward_list< std::size_t > > edges_;
    std::vector< bool > hasVertex_;

    static void pathMaker(void* data, std::size_t x, std::size_t y);
  };
}

#endif
