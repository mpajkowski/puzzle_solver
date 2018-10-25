#include "AstrStrategy.hpp"
#include "State.hpp"

AstrStrategy::AstrStrategy(State initialState)
  : Strategy{ std::move(initialState) }
{}

auto AstrStrategy::findSolution() -> Solution
{
  return {};
}
