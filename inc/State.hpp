#pragma once
#include <cstdint>
#include <type_traits>
#include <vector>

class State
{
public:
  enum class Operator
  {
    Left,
    Right,
    Up,
    Down,
  };

  State(std::uint8_t col, std::vector<std::uint8_t> board);
  State(State const&) = default;
  auto operator=(State const&) -> State& = default;
  State(State&&) = default;
  auto operator=(State &&) -> State& = default;
  ~State() = default;

  auto operator==(State const& rhs) -> bool;
  auto operator!=(State const& rhs) -> bool;

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
