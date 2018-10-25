#include "BfsStrategy.hpp"
#include "State.hpp"

BfsStrategy::BfsStrategy(State initialState, Constants::Order order)
  : Strategy{ std::move(initialState) }
  , order{ order }
{}

auto BfsStrategy::findSolution() -> Solution
{
  return {};
}
