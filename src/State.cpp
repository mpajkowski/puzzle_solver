#include "State.hpp"
#include <iomanip>
#include <sstream>

State::State(std::uint8_t col, std::vector<std::uint8_t> board)
  : col{ col }
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
  return this->board != rhs.board;
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
  return zeroPos < board.size() - col - 1;
}

template<State::Operator Op>
auto State::takeActionInternal(int zeroPosShift) -> bool
{
  if (canMove<Op>()) {
    std::swap(board[zeroPos], board[zeroPos + zeroPosShift]);

    // update cache
    zeroPos += zeroPosShift;
    return true;
  }

  return false;
}

template<>
auto State::takeAction<State::Operator::Left>() -> bool
{
  return takeActionInternal<State::Operator::Left>(-1);
}

template<>
auto State::takeAction<State::Operator::Right>() -> bool
{
  return takeActionInternal<State::Operator::Right>(+1);
}

template<>
auto State::takeAction<State::Operator::Up>() -> bool
{
  return takeActionInternal<State::Operator::Up>(-col);
}

template<>
auto State::takeAction<State::Operator::Down>() -> bool
{
  return takeActionInternal<State::Operator::Down>(+col);
}

auto State::getCol() const -> std::uint8_t
{
  return col;
}

auto State::toString() const -> std::string
{
  auto stream = std::ostringstream{};

  stream << "Columns: " << static_cast<int>(col) << ", board: {";

  for (auto number : board) {
    stream << std::setw(3) << static_cast<int>(number) << ' ';
  }

  stream << " }";

  return stream.str();
}

auto operator<<(std::ostream& os, State const& state) -> std::ostream&
{
  os << state.toString();
  return os;
}
