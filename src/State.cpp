#include "State.hpp"
#include <iomanip>
#include <sstream>

State::State(State::ValueType row, State::ValueType col, std::vector<State::ValueType> board)
  : row{ row }
  , col{ col }
  , zeroPos{ 0 }
  , board{ std::move(board) }
{
  init();
}

auto State::init() -> void
{
  for (std::size_t i = 0; i < board.size(); ++i) {
    if (board[i] == 0) {
      zeroPos = i;
      break;
    }
  }
}

auto State::operator==(State const& rhs) const -> bool
{
  return this->board == rhs.board;
}

auto State::operator!=(State const& rhs) const -> bool
{
  return !(operator==(rhs));
}

template<>
auto State::canMove<State::Operator::Left>() -> bool
{
  return zeroPos % col != 0;
}

template<>
auto State::canMove<State::Operator::Right>() -> bool
{
  return (zeroPos + 1) % col != 0;
}

template<>
auto State::canMove<State::Operator::Up>() -> bool
{
  return zeroPos >= col;
}

template<>
auto State::canMove<State::Operator::Down>() -> bool
{
  return zeroPos < board.size() - col;
}

template<State::Operator Op>
auto State::moveInternal(int zeroPosShift) -> std::optional<State::Operator>
{
  if (canMove<Op>()) {
    std::swap(board[zeroPos], board[zeroPos + zeroPosShift]);

    // update cache
    zeroPos += zeroPosShift;
    return Op;
  }

  return std::nullopt;
}

auto State::move(State::Operator op) -> std::optional<State::Operator>
{
  switch (op) {
    case State::Operator::Left:
      return moveInternal<State::Operator::Left>(-1);
    case State::Operator::Right:
      return moveInternal<State::Operator::Right>(+1);
    case State::Operator::Up:
      return moveInternal<State::Operator::Up>(-col);
    case State::Operator::Down:
      return moveInternal<State::Operator::Down>(+col);
  }
}

auto State::getCol() const -> State::ValueType
{
  return col;
}

auto State::getRow() const -> State::ValueType
{
  return row;
}

auto State::getBoard() const -> std::vector<State::ValueType> const&
{
  return board;
}

auto State::toString() const -> std::string
{
  auto stream = std::ostringstream{};

  stream << "{";

  for (std::size_t i = 0; i < board.size(); ++i) {
    if (i % col == 0) {
      stream << "\n";
    }

    stream << std::setw(3) << static_cast<int>(board[i]) << ' ';
  }

  stream << "\n}";

  return stream.str();
}

auto operator<<(std::ostream& os, State const& state) -> std::ostream&
{
  os << state.toString();
  return os;
}
