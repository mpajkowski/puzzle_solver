#include "State.hpp"

State::State(std::uint8_t col, std::vector<std::uint8_t> board)
  : col{ col }
  , zeroPos{ 0 }
  , board{ std::move(board) }
{
  for (std::size_t i = 0; i < board.size(); ++i) {
    if (board[i] == 0) {
      this->zeroPos = i;
      break;
    }
  }
}

auto State::operator==(State const& rhs) -> bool
{
  return this->board == rhs.board;
}

auto State::operator!=(State const& rhs) -> bool
{
  return this->board != rhs.board;
}

template<>
auto State::canMove<State::Operator::Left>() -> bool
{
  return zeroPos % col == 0;
}

template<>
auto State::canMove<State::Operator::Right>() -> bool
{
  return zeroPos % col == col - 1;
}

template<>
auto State::canMove<State::Operator::Up>() -> bool
{
  return zeroPos > col - 1;
}

template<>
auto State::canMove<State::Operator::Down>() -> bool
{
  return zeroPos < board.size() - col - 1;
}

template<State::Operator Op>
auto State::takeActionInternal(int zeroPosShift) -> State&
{
  if (canMove<Op>()) {
    std::swap(board[zeroPos], board[zeroPos + zeroPosShift]);

    // update cache
    zeroPos += zeroPosShift;
  }

  return *this;
}

template<>
auto State::takeAction<State::Operator::Left>() -> State&
{
  return takeActionInternal<State::Operator::Left>(+1);
}

template<>
auto State::takeAction<State::Operator::Right>() -> State&
{
  return takeActionInternal<State::Operator::Right>(-1);
}

template<>
auto State::takeAction<State::Operator::Up>() -> State&
{
  return takeActionInternal<State::Operator::Up>(+col);
}

template<>
auto State::takeAction<State::Operator::Down>() -> State&
{
  return takeActionInternal<State::Operator::Down>(-col);
}
