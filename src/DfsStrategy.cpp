#include "DfsStrategy.hpp"
#include "State.hpp"

DfsStrategy::DfsStrategy(State initialState, Constants::Order order)
  : Strategy{ std::move(initialState) }
  , order{ order }
{}

auto DfsStrategy::findSolution() -> Solution
{
  // TODO implement
  return {};
}
