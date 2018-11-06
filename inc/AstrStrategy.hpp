#pragma once
#include "Constants.hpp"
#include "State.hpp"
#include "Strategy.hpp"
#include <functional>

class StrategyContext;

using HeuristicFn = std::function<State::ValueType(State const&, State const&)>;

auto hamming(State const&, State const&) -> State::ValueType;
auto manhattan(State const&, State const&) -> State::ValueType;

class AstrStrategy : public Strategy
{
public:
  AstrStrategy(Constants::Heuristic heuristic);
  auto findSolution(StrategyContext&& strategyContext) -> Solution override;

private:
  HeuristicFn heuristicFn;
};

