#pragma once
#include <chrono>
#include <cstdint>
#include <string>

struct Solution
{
  std::string operators;
  uint64_t visitedStatesCount;
  uint64_t processedStatesCount;
  uint64_t maxRecursionDepth;
  std::chrono::milliseconds duration;

  Solution() = default;

  Solution(Solution&&) = default;
  auto operator=(Solution &&) -> Solution& = default;

  Solution(Solution const&) = delete;
  auto operator=(Solution const&) -> Solution& = default;
};
