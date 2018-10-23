#pragma once
#include <cstdint>
#include <type_traits>
#include <vector>

class State
{
public:
  State(std::uint8_t col, std::vector<std::uint8_t> board);

  enum class Operator
  {
    Left,
    Right,
    Up,
    Down,
  };

  template<Operator>
  auto takeAction() -> State&;

private:
  template<Operator>
  auto canMove() -> bool;

  template<Operator>
  auto takeActionInternal(int zeroPosShift) -> State&;

  int col;
  std::size_t zeroPos;
  std::vector<std::uint8_t> board;

  friend class StateTest_readingFile_Test;
};
