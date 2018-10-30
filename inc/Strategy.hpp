#pragma once
#include "Solution.hpp"
#include <chrono>

class StrategyContext;

using Clock = std::chrono::high_resolution_clock;

class Strategy
{
public:
  auto virtual findSolution(StrategyContext&& stateContext) -> Solution = 0;
  virtual ~Strategy() = default;
};
