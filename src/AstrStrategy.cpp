#include "AstrStrategy.hpp"
#include "State.hpp"

AstrStrategy::AstrStrategy(State state)
  : Strategy{ std::move(state) }
{}

auto AstrStrategy::findSolution() -> Solution
{
  return {};
}
