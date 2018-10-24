#include "DfsStrategy.hpp"
#include "State.hpp"

DfsStrategy::DfsStrategy(State state, Constants::Order order)
  : Strategy{ std::move(state) }
  , order{ order }
{}

auto DfsStrategy::findSolution() -> Solution
{
  // TODO implement
  return {};
}
