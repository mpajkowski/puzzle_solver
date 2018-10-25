#include "BfsStrategy.hpp"
#include "State.hpp"

BfsStrategy::BfsStrategy(Constants::Order order)
  : order{ order }
{}

auto BfsStrategy::findSolution(StrategyContext&& strategyContext) -> Solution
{
  return {};
}
