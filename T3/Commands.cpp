#include "Commands.hpp"
#include <iostream>
#include <exception>
#include <algorithm>
#include <numeric>
#include "AddPolygonAreaIf.hpp"

klyukin::Commands::Commands(const std::vector< Polygon >& v, std::istream& in, std::ostream& out):
  polygons_(v),
  in_(in),
  out_(out)
{}

void klyukin::Commands::initPolygonConditionByCmd(PolygonCondition& cond, const std::string& cmd)
{
  if (cmd == "EVEN")
  {
    cond.setMode(PolygonCondition::hasEvenVerticesCount);
  }
  else if (cmd == "ODD")
  {
    cond.setMode(PolygonCondition::hasOddVerticesCount);
  }
  else
  {
    std::size_t n = std::atoi(cmd.c_str());
    const std::size_t MINIMAL_POINTS_COUNT_FOR_CMD = 3;
    if (n < MINIMAL_POINTS_COUNT_FOR_CMD)
    {
      throw std::logic_error("few points");
    }
    cond.setMode(PolygonCondition::hasNVertices);
    cond.setNVertices(n);
  }
}

void klyukin::Commands::doCount()
{
  std::string str;
  PolygonCondition cond;
  in_ >> str;
  initPolygonConditionByCmd(cond, str);
  out_ << std::count_if(polygons_.begin(), polygons_.end(), cond) << '\n';
}


void klyukin::Commands::doArea()
{
  std::string str;
  PolygonCondition cond;
  in_ >> str;
  if (str != "MEAN")
  {
    initPolygonConditionByCmd(cond, str);
  }
  double area = std::accumulate(
    polygons_.begin(), polygons_.end(), 0.0, AddPolygonAreaIf{cond}
  );
  if (str == "MEAN")
  {
    if (!polygons_.empty())
    {
      area /= polygons_.size();
    }
    else
    {
      throw std::logic_error("cant calculate mean");
    }
  }
  out_ << area << '\n';
}

std::vector< klyukin::Polygon >::const_iterator klyukin::Commands::findMaxOrMinPolygon(
    const PolygonComparator& compare, bool min)
{
  std::vector< Polygon >::const_iterator pos;
  if (min)
  {
    pos = std::min_element(polygons_.begin(), polygons_.end(), compare);
  }
  else
  {
    pos = std::max_element(polygons_.begin(), polygons_.end(), compare);
  }
  if (pos == polygons_.end())
  {
    throw std::logic_error("cant find max or min");
  }
  return pos;
}

using namespace std::placeholders;
static const klyukin::Commands::PolygonComparator comparePolygonByArea =
std::bind(
  std::less< double >(),
  std::bind(&klyukin::Polygon::getArea, _1),
  std::bind(&klyukin::Polygon::getArea, _2)
);
static const klyukin::Commands::PolygonComparator comparePolygonByVerticesCount =
std::bind(
  std::less< std::size_t >(),
  std::bind(&std::vector< klyukin::Point >::size,
    std::bind(&klyukin::Polygon::points, _1)),
  std::bind(&std::vector< klyukin::Point >::size,
    std::bind(&klyukin::Polygon::points, _2))
);

void klyukin::Commands::handleMaxOrMinCmdByAreaOrVertexesCmd(const std::string& cmd, bool min)
{
  if (cmd == "AREA")
  {
    out_ << findMaxOrMinPolygon(comparePolygonByArea, min)->getArea() << '\n';
  }
  else if (cmd == "VERTEXES")
  {
    out_ << findMaxOrMinPolygon(comparePolygonByVerticesCount, min)->points.size() << '\n';
  }
  else
  {
    throw std::logic_error("bad cmd for MIN or MAX");
  }
}

void klyukin::Commands::doMax()
{
  std::string str;
  in_ >> str;
  handleMaxOrMinCmdByAreaOrVertexesCmd(str, false);
}

void klyukin::Commands::doMin()
{
  std::string str;
  in_ >> str;
  handleMaxOrMinCmdByAreaOrVertexesCmd(str, true);
}

void klyukin::Commands::doRects()
{
  out_ << std::count_if(polygons_.begin(), polygons_.end(),
    std::bind(&klyukin::Polygon::isRectangle, _1)
  ) << '\n';
}

void klyukin::Commands::doRightShapes()
{
  out_ << std::count_if(polygons_.begin(), polygons_.end(),
    std::bind(&klyukin::Polygon::hasRightAngle, _1)
  ) << '\n';
}
