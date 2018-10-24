#pragma once
#include <chrono>
#include <cstdint>

struct Solution
{
  uint64_t length;
  uint64_t visitedStatesCount;
  uint64_t processedStatesCount;
  uint64_t maxRecursionDepth;
  std::chrono::seconds duration;

  Solution() = default;

  Solution(Solution&&) = default;
  auto operator=(Solution &&) -> Solution& = default;

  Solution(Solution const&) = delete;
  auto operator=(Solution const&) -> Solution& = default;
};
