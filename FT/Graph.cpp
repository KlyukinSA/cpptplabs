#include "Graph.hpp"
#include <stdexcept>
#include <iostream>
#include <queue>
#include <algorithm>

klyukin::Graph::Graph(std::size_t size):
  capacity_(size),
  edges_(size),
  hasVertex_(size, false)
{}

bool klyukin::Graph::hasVertex(std::size_t i) const
{
  if (i >= capacity_)
  {
    return false;
  }
  return hasVertex_[i];
}

bool klyukin::Graph::hasVertices() const
{
  return std::find(hasVertex_.cbegin(), hasVertex_.cend(), true) != hasVertex_.cend();
}

bool klyukin::Graph::hasEdge(std::size_t x, std::size_t y) const
{
  if (x >= capacity_ || y >= capacity_)
  {
    return false;
  }
  return std::find(edges_[x].cbegin(), edges_[x].cend(), y) != edges_[x].cend();
}

std::size_t klyukin::Graph::addVertex(const std::vector< std::size_t >& adjacentVertices)
{
  std::size_t pos = 0;
  while (pos < capacity_ && hasVertex_[pos])
  {
    pos++;
  }
  if (pos == capacity_)
  {
    throw std::range_error("Graph: overflow");
  }
  for (std::size_t adj: adjacentVertices)
  {
    if (adj < capacity_ && hasVertex_[adj])
    {
      edges_[pos].push_front(adj);
      edges_[adj].push_front(pos);
    }
  }
  hasVertex_[pos] = true;
  return pos;
}

bool klyukin::Graph::removeVertex(std::size_t pos)
{
  if (pos >= capacity_ || !hasVertex_[pos])
  {
    return false;
  }
  for (std::size_t adj: edges_[pos])
  {
    edges_[adj].remove(pos);
  }
  edges_[pos].clear();
  hasVertex_[pos] = false;
  return true;
}

void klyukin::Graph::breadthFirstSearch(std::size_t start,
  void* data, void (*processEdge)(void* data, std::size_t x, std::size_t y)) const
{
  if (start >= capacity_ || !hasVertex_[start])
  {
    return;
  }
  std::queue< std::size_t > q;
  std::size_t v = start;
  std::vector< bool > discovered(capacity_, false);
  q.push(v);
  discovered[v] = true;
  while (!q.empty())
  {
    v = q.front();
    q.pop();
    for (std::size_t adj: edges_[v])
    {
      if (!discovered[adj])
      {
        q.push(adj);
        discovered[adj] = true;
        processEdge(data, v, adj);
      }
    }
  }
}

void klyukin::Graph::pathMaker(void* data, std::size_t x, std::size_t y)
{
  std::vector< std::size_t >& path = *((std::vector< std::size_t >*)(data));
  path[y] = path[x] + 1;
}

void klyukin::Graph::getPath(std::size_t start, std::ostream& out) const
{
  if (start >= capacity_ || !hasVertex_[start])
  {
    return;
  }
  std::vector< std::size_t > path(capacity_, 0);
  path[start] = 0;
  breadthFirstSearch(start, &path, pathMaker);
  out << "path to _ is _\n";
  for (std::size_t i = 0; i < capacity_; i++)
  {
    if (hasVertex_[i])
    {
      out << i << " : " << path[i] << '\n';
    }
  }
}

std::size_t klyukin::Graph::getDiameter(std::size_t start) const
{
  if (start >= capacity_ || !hasVertex_[start])
  {
    return 0;
  }
  std::vector< std::size_t > path(capacity_, 0);
  path[start] = 0;
  breadthFirstSearch(start, &path, pathMaker);
  std::size_t max = 0;
  for (std::size_t i = 0; i < capacity_; i++)
  {
    if (hasVertex_[i] && path[i] > max)
    {
      max = path[i];
      start = i;
    }
  }
  path[start] = 0;
  breadthFirstSearch(start, &path, pathMaker);
  for (std::size_t i = 0; i < capacity_; i++)
  {
    if (hasVertex_[i] && path[i] > max)
    {
      max = path[i];
    }
  }
  return max;
}
