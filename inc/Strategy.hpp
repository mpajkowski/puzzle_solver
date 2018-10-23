#pragma once
#include <chrono>
#include <memory>
#include <tuple>

class State;

class Strategy
{
public:
  Strategy(std::unique_ptr<State> state);
  virtual auto findSolution() -> std::tuple<uint64_t, // solution length
                                            uint64_t, // visited states count
                                            uint64_t, // processed states count
                                            uint64_t, // max recursion depth
                                            std::chrono::seconds> = 0;

  virtual ~Strategy() = default;

protected:
  std::unique_ptr<State> state;
};
