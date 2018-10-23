#include "State.hpp"
#include "StateParser.hpp"
#include <gtest/gtest.h>

TEST(StateTest, readingFile)
{
  // TODO: handle runtime path in cmake
  // Temp solution - run from root build directory
  constexpr std::size_t BOARD_SIZE{ 16 };
  constexpr std::size_t COL_AND_ROW{ 4 };
  auto stateParser = StateParser{ "../../test/test_puzzle.txt" };
  auto state = stateParser.parse();

  ASSERT_EQ(state->board.size(), BOARD_SIZE);
  ASSERT_EQ(state->col, COL_AND_ROW);
  ASSERT_EQ(state->row, COL_AND_ROW);
}
