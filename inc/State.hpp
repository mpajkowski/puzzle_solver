#pragma once

#include <cstdint>
#include <functional>
#include <optional>
#include <string>
#include <vector>

class State
{
public:
  using ValueType = std::uint_fast8_t;

  enum class Operator : char
  {
    Left = 'L',
    Right = 'R',
    Up = 'U',
    Down = 'D'
  };

  State(State::ValueType row, State::ValueType col, std::vector<State::ValueType> board);

  State(State const&) = default;
  auto operator=(State const&) -> State& = default;
  State(State&&) = default;
  auto operator=(State &&) -> State& = default;
  ~State() = default;

  auto operator==(State const& rhs) const -> bool;
  auto operator!=(State const& rhs) const -> bool;

  auto move(Operator op) -> std::optional<Operator>;

  auto getCol() const -> ValueType;
  auto getRow() const -> ValueType;
  auto toString() const -> std::string;

private:
  auto init() -> void;

  template<Operator>
  auto canMove() -> bool;

  template<Operator>
  auto moveInternal(int zeroPosShift) -> std::optional<Operator>;

  ValueType row;
  ValueType col;
  std::size_t zeroPos;
  std::vector<ValueType> board;

  friend class StateTest_readingFile_Test;

  friend auto operator<<(std::ostream& os, State const&) -> std::ostream&;
  friend struct std::hash<State>;
};

template<>
struct std::hash<State>
{
  std::size_t operator()(const State& s) const
  {
    auto hasher = std::hash<State::ValueType>{};
    std::size_t seed = s.board.size();
    for (auto it : s.board) {
      seed ^= hasher(it) << 1;
    }
    return seed;
  }
};
