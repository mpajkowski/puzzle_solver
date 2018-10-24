#pragma once

#include <cstdint>
#include <string>
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

  auto operator==(State const& rhs) const -> bool;
  auto operator!=(State const& rhs) const -> bool;

  template<Operator>
  auto takeAction() -> bool;

  auto toString() const -> std::string;

private:
  auto init() -> void;

  template<Operator>
  auto canMove() -> bool;

  template<Operator>
  auto takeActionInternal(int zeroPosShift) -> bool;

  int col;
  std::size_t zeroPos;
  std::vector<std::uint8_t> board;

  friend class StateTest_readingFile_Test;

  friend auto operator<<(std::ostream& os, State const&) -> std::ostream&;
};

auto operator<<(std::ostream& os, State const&) -> std::ostream&;
