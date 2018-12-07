#pragma once
#include "Constants.hpp"
#include "State.hpp"
#include "Strategy.hpp"
#include <functional>

class StrategyContext;

using HeuristicFn = std::function<State::ValueType(State const&)>;

class AstrStrategy final : public Strategy
{
public:
  AstrStrategy(StrategyContext strategyContext, Constants::Heuristic heuristic);
  auto findSolution() -> Solution override;

private:
  HeuristicFn heuristicFn;

  auto hamming(State const&) -> int;
  auto manhattan(State const&) -> int;
};

