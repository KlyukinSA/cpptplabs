#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <iosfwd>
#include <string>
#include <functional>
#include "base-types.hpp"
#include "PolygonCondition.hpp"

namespace klyukin
{
  class Commands
  {
    public:
      using PolygonComparator = std::function< bool (Polygon, Polygon) >;
      Commands(const std::vector< Polygon >& v, std::istream& in, std::ostream& out);
      void doCount();
      void doArea();
      void doMax();
      void doMin();
      void doRects();
      void doRightShapes();

    private:
      const std::vector< Polygon >& polygons_;
      std::istream& in_;
      std::ostream& out_;

      static void initPolygonConditionByCmd(PolygonCondition& cond, const std::string& cmd);
      std::vector< Polygon >::const_iterator findMaxOrMinPolygon(
          const PolygonComparator& compare, bool min);
      void handleMaxOrMinCmdByAreaOrVertexesCmd(const std::string& cmd, bool min);
  };
}

#endif
