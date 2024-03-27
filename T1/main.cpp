#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>
#include <iomanip>
#include "rectangle.hpp"
#include "circle.hpp"
#include "regular.hpp"
#include "Family.hpp"

namespace klyukin
{
  static void readDoubles(klyukin::Family< double >& d, int n)
  {
    std::string line;
    std::getline(std::cin, line, '\n');
    int pos1 = 1;
    int pos2 = line.find(' ', pos1);
    for (int i = 0; i < n; i++)
    {
      if (pos1 == 0 && pos2 == 0)
      {
        throw std::range_error("readDoubles: not enough doubles");
      }
      d.add(std::strtod(line.substr(pos1, pos2).c_str(), nullptr));
      pos1 = pos2 + 1;
      pos2 = line.find(' ', pos1);
    }
  }

  void printInfoShapes(const Family< std::shared_ptr< Shape > >& shapes)
  {
    double s = 0;
    for (std::size_t i = 0; i < shapes.getSize(); i++)
    {
      s += shapes[i]->getArea();
    }
    std::cout << s << ' ';
    for (std::size_t i = 0; i < shapes.getSize() - 1; i++)
    {
      std::cout << shapes[i]->getFrameRect() << ' ';
    }
    std::cout << shapes[shapes.getSize() - 1]->getFrameRect() << '\n';
  }

  void scaleShapeRelativeToPoint(const std::shared_ptr< Shape >& shape, double k, point_t p)
  {
    shape->scale(k);
    double x = shape->getFrameRect().pos.x;
    double y = shape->getFrameRect().pos.y;
    shape->move({k * x + (1 - k) * p.x, k * y + (1 - k) * p.y});
  }
}

int main()
{
  std::cout << std::fixed;
  std::cout << std::setprecision(1);
  klyukin::Family< std::shared_ptr< klyukin::Shape > > shapes;
  std::string s;
  const int nRectangle = 4;
  const int nCircle = 3;
  const int nRegular = 6;
  bool readBad = false;
  bool wereScale = false;
  while (std::cin >> s)
  {
    try
    {
      if (s == "RECTANGLE")
      {
        klyukin::Family< double > d;
        klyukin::readDoubles(d, nRectangle);
        shapes.add(std::shared_ptr< klyukin::Shape >(
          new klyukin::Rectangle({d[0], d[1]}, {d[2], d[3]})));
      }
      else if (s == "CIRCLE")
      {
        klyukin::Family< double > d;
        klyukin::readDoubles(d, nCircle);
        shapes.add(std::shared_ptr< klyukin::Shape >(
          new klyukin::Circle({d[0], d[1]}, d[2])));
      }
      else if (s == "REGULAR")
      {
        klyukin::Family< double > d;
        klyukin::readDoubles(d, nRegular);
        shapes.add(std::shared_ptr< klyukin::Shape >(
          new klyukin::Regular({d[0], d[1]}, {d[2], d[3]}, {d[4], d[5]})));
      }
      else if (s == "SCALE")
      {
        wereScale = true;
        double scaleX, scaleY, k;
        std::cin >> scaleX >> scaleY >> k;
        if (!std::cin || k < 0 || !shapes.getSize())
        {
          std::cerr << "scale error\n";
          return 2;
        }
        else
        {
          printInfoShapes(shapes);
          for (std::size_t i = 0; i < shapes.getSize(); i++)
          {
            scaleShapeRelativeToPoint(shapes[i], k, {scaleX, scaleY});
          }
          printInfoShapes(shapes);
          if (readBad)
          {
            std::cerr << "there are shape errors\n";
          }
        }
        break;
      }
    }
    catch (const std::range_error& e)
    {
      readBad = true;
    }
  }
  if (!wereScale)
  {
    std::cerr << "scale error\n";
    return 2;
  }
  return 0;
}
