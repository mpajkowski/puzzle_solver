#include "DfsStrategy.hpp"
#include "State.hpp"

DfsStrategy::DfsStrategy(std::unique_ptr<State> state)
  : Strategy{ std::move(state) }
{}

auto DfsStrategy::findSolution() -> std::tuple<uint64_t, // solution length
                                               uint64_t, // visited states count
                                               uint64_t, // processed states count
                                               uint64_t, // max recursion depth
                                               std::chrono::seconds>
{
  // TODO implement
  return {};
}
