#pragma once
#include "Solution.hpp"
#include "StrategyContext.hpp"
#include <chrono>

using Clock = std::chrono::high_resolution_clock;
class Node;

class Strategy
{
public:
  Strategy(StrategyContext strategyContext);
  virtual ~Strategy() = default;
  auto virtual findSolution() -> Solution = 0;

protected:
  auto constructPath(std::shared_ptr<Node> const&) -> std::string;
  StrategyContext strategyContext;
};
