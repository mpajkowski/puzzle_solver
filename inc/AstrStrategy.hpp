#pragma once
#include "Constants.hpp"
#include "State.hpp"
#include "Strategy.hpp"
#include <functional>
#include <map>

class StrategyContext;

using HeuristicFn = std::function<State::ValueType(State const&)>;

class AstrStrategy final : public Strategy
{
public:
  AstrStrategy(StrategyContext strategyContext, Constants::Heuristic heuristic);
  auto findSolution() -> Solution override;

private:
  HeuristicFn heuristicFn;
  std::map<std::size_t, State::Point> goalCache;

  auto hamming(State const&) -> State::ValueType;
  auto manhattan(State const&) -> State::ValueType;
};

