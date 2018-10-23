#pragma once
#include <cstdint>
#include <vector>

struct State
{
  std::uint8_t col;
  std::uint8_t row;
  std::vector<std::uint8_t> board;
};
