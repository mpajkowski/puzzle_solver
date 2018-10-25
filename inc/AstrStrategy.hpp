#pragma once
#include "Strategy.hpp"

class AstrStrategy : public Strategy
{
public:
  AstrStrategy(State initialState);
  auto findSolution() -> Solution;
};
