#pragma once
#include "Strategy.hpp"

class AstrStrategy : public Strategy
{
public:
  AstrStrategy(State state);
  auto findSolution() -> Solution;
};
