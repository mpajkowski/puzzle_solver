#include "DfsStrategy.hpp"
#include "State.hpp"

DfsStrategy::DfsStrategy(std::vector<State::Operator> const& order)
  : order{ order }
{}

auto DfsStrategy::findSolution(StrategyContext&& strategyContext) -> Solution
{
  // TODO implement
  return {};
}
