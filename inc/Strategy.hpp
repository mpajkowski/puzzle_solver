#pragma once
#include "Solution.hpp"

class StrategyContext;

class Strategy
{
public:
  auto virtual findSolution(StrategyContext&& stateContext) -> Solution = 0;
  virtual ~Strategy() = default;
};
