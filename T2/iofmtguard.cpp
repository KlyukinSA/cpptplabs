#include "iofmtguard.hpp"

klyukin::iofmtguard::iofmtguard(std::basic_ios< char >& s):
  s_(s),
  precision_(s.precision()),
  flags_(s.flags())
{}
klyukin::iofmtguard::~iofmtguard()
{
  s_.precision(precision_);
  s_.flags(flags_);
}
