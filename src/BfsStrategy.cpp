#include "BfsStrategy.hpp"
#include "State.hpp"

BfsStrategy::BfsStrategy(State state, Constants::Order order)
  : Strategy{ std::move(state) }
  , order{ order }
{}

auto BfsStrategy::findSolution() -> Solution
{
  return {};
}
