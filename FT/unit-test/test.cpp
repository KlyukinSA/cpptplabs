#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GraphTest
#include <boost/test/unit_test.hpp>

#include <fstream>
#include "../GraphCmdLoop.hpp"

static bool checkTestCase(const std::string& caseName)
{
  std::string outFileName = "output.txt";
  std::ofstream out(outFileName);
  std::ofstream log("../input.log");
  std::string path = "tests/";
  std::ifstream in(path + caseName + ".txt");
  klyukin::doGraphCmdLoop(in, out, log, false);
  in.close();
  log.close();
  out.close();
  std::ifstream result(outFileName);
  std::string resultContents{std::istreambuf_iterator<char>(result), std::istreambuf_iterator<char>()};
  result.close();
  std::ifstream expect(path + caseName + ".expect");
  std::string expectContents{std::istreambuf_iterator<char>(expect), std::istreambuf_iterator<char>()};
  expect.close();
  return resultContents == expectContents;
}

BOOST_AUTO_TEST_CASE(common)
{
  BOOST_CHECK(checkTestCase("common"));
}

BOOST_AUTO_TEST_CASE(bfs)
{
  BOOST_CHECK(checkTestCase("bfs"));
}

BOOST_AUTO_TEST_CASE(getPath)
{
  BOOST_CHECK(checkTestCase("getPath"));
}

BOOST_AUTO_TEST_CASE(getDiameter)
{
  BOOST_CHECK(checkTestCase("getDiameter"));
}
