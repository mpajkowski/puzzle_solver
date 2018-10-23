#pragma once
#include "Strategy.hpp"

class DfsStrategy : public Strategy
{
public:
  DfsStrategy(std::unique_ptr<State> state);
  auto findSolution() -> std::tuple<uint64_t, // solution length
                                    uint64_t, // visited states count
                                    uint64_t, // processed states count
                                    uint64_t, // max recursion depth
                                    std::chrono::seconds> override;
};
