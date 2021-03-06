#include "State.hpp"
#include "StateParser.hpp"
#include <gtest/gtest.h>
#include <unordered_set>

TEST(StateTest, readingFile)
{
  // TODO: handle runtime path in cmake
  // Temp solution - run from root build directory
  constexpr std::size_t BOARD_SIZE{ 16 };
  constexpr std::size_t COL{ 4 };
  auto stateParser = StateParser{ "../../test/test_puzzle.txt" };
  auto state = stateParser.parse();

  ASSERT_EQ(state->board.size(), BOARD_SIZE);
  ASSERT_EQ(state->col, COL);
}

TEST(StateTest, operatorRight)
{
  auto destinationState = State(4, 4, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0 });
  auto moveRightOncetoWin = State(4, 4, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 15 });

  ASSERT_NE(destinationState, moveRightOncetoWin);

  EXPECT_TRUE(moveRightOncetoWin.move(State::Operator::Right));
  EXPECT_EQ(destinationState, moveRightOncetoWin);
}

TEST(StateTest, operatorLeft)
{
  auto startState = State(4, 4, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 15 });
  auto wantedState = State(4, 4, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 14, 15 });

  ASSERT_NE(startState, wantedState);
  EXPECT_TRUE(startState.move(State::Operator::Left));

  EXPECT_EQ(startState, wantedState);
}

TEST(StateTest, operatorUp)
{
  auto startState = State(4, 4, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 15 });
  auto wantedState = State(4, 4, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 12, 13, 14, 11, 15 });

  ASSERT_NE(startState, wantedState);
  EXPECT_TRUE(startState.move(State::Operator::Up));

  EXPECT_EQ(startState, wantedState);
}

TEST(StateTest, operatorDown)
{
  auto startState = State(4, 4, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 12, 13, 14, 11, 15 });
  auto wantedState = State(4, 4, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 15 });

  ASSERT_NE(startState, wantedState);
  EXPECT_TRUE(startState.move(State::Operator::Down));

  EXPECT_EQ(startState, wantedState);
}

TEST(StateTest, returnToInitialState)
{
  auto startState = State(4, 4, { 7, 12, 4, 9, 5, 10, 6, 1, 3, 13, 8, 0, 14, 2, 11, 15 });
  auto wantedState = State(4, 4, { 7, 12, 4, 9, 5, 10, 6, 1, 3, 13, 8, 0, 14, 2, 11, 15 });

  EXPECT_TRUE(startState.move(State::Operator::Up));
  EXPECT_TRUE(startState.move(State::Operator::Left));
  EXPECT_TRUE(startState.move(State::Operator::Down));
  EXPECT_TRUE(startState.move(State::Operator::Right));
  EXPECT_TRUE(startState.move(State::Operator::Up));
  EXPECT_TRUE(startState.move(State::Operator::Left));
  EXPECT_TRUE(startState.move(State::Operator::Down));
  EXPECT_TRUE(startState.move(State::Operator::Right));
  EXPECT_TRUE(startState.move(State::Operator::Up));
  EXPECT_TRUE(startState.move(State::Operator::Left));
  EXPECT_TRUE(startState.move(State::Operator::Down));
  EXPECT_TRUE(startState.move(State::Operator::Right));

  EXPECT_EQ(startState, wantedState);
}

TEST(StateTest, illegalMovesLeft)
{
  {
    auto state = State(4, 4, { 0, 12, 4, 9, 5, 10, 6, 1, 3, 13, 8, 7, 14, 2, 11, 15 });
    EXPECT_FALSE(state.move(State::Operator::Left));
  }

  {
    auto state = State(4, 4, { 7, 12, 4, 9, 0, 10, 6, 1, 3, 13, 8, 5, 14, 2, 11, 15 });
    EXPECT_FALSE(state.move(State::Operator::Left));
  }

  {
    auto state = State(4, 4, { 7, 12, 4, 9, 3, 10, 6, 1, 0, 13, 8, 5, 14, 2, 11, 15 });
    EXPECT_FALSE(state.move(State::Operator::Left));
  }

  {
    auto state = State(4, 4, { 7, 12, 4, 9, 3, 10, 6, 1, 14, 13, 8, 5, 0, 2, 11, 15 });
    EXPECT_FALSE(state.move(State::Operator::Left));
  }
}

TEST(StateTest, illegalMovesRight)
{
  {
    auto state = State(4, 4, { 9, 12, 4, 0, 5, 10, 6, 1, 3, 13, 8, 7, 14, 2, 11, 15 });
    EXPECT_FALSE(state.move(State::Operator::Right));
  }

  {
    auto state = State(4, 4, { 9, 12, 4, 1, 5, 10, 6, 0, 3, 13, 8, 7, 14, 2, 11, 15 });
    EXPECT_FALSE(state.move(State::Operator::Right));
  }

  {
    auto state = State(4, 4, { 9, 12, 4, 1, 5, 10, 6, 7, 3, 13, 8, 0, 14, 2, 11, 15 });
    EXPECT_FALSE(state.move(State::Operator::Right));
  }

  {
    auto state = State(4, 4, { 9, 12, 4, 1, 5, 10, 6, 7, 3, 13, 8, 15, 14, 2, 11, 0 });
    EXPECT_FALSE(state.move(State::Operator::Right));
  }
}

TEST(StateTest, illegalMovesUp)
{
  {
    auto state = State(4, 4, { 0, 12, 4, 9, 5, 10, 6, 1, 3, 13, 8, 7, 14, 2, 11, 15 });
    EXPECT_FALSE(state.move(State::Operator::Up));
  }

  {
    auto state = State(4, 4, { 12, 0, 4, 9, 5, 10, 6, 1, 3, 13, 8, 7, 14, 2, 11, 15 });
    EXPECT_FALSE(state.move(State::Operator::Up));
  }

  {
    auto state = State(4, 4, { 12, 4, 0, 9, 5, 10, 6, 1, 3, 13, 8, 7, 14, 2, 11, 15 });
    EXPECT_FALSE(state.move(State::Operator::Up));
  }

  {
    auto state = State(4, 4, { 12, 4, 9, 0, 5, 10, 6, 1, 3, 13, 8, 7, 14, 2, 11, 15 });
    EXPECT_FALSE(state.move(State::Operator::Up));
  }
}

TEST(StateTest, illegalMovesDown)
{
  {
    auto state = State(4, 4, { 14, 12, 4, 9, 5, 10, 6, 1, 3, 13, 8, 7, 0, 2, 11, 15 });
    EXPECT_FALSE(state.move(State::Operator::Down));
  }

  {
    auto state = State(4, 4, { 14, 12, 4, 9, 5, 10, 6, 1, 3, 13, 8, 7, 2, 0, 11, 15 });
    EXPECT_FALSE(state.move(State::Operator::Down));
  }

  {
    auto state = State(4, 4, { 14, 12, 4, 9, 5, 10, 6, 1, 3, 13, 8, 7, 2, 11, 0, 15 });
    EXPECT_FALSE(state.move(State::Operator::Down));
  }

  {
    auto state = State(4, 4, { 14, 12, 4, 9, 5, 10, 6, 1, 3, 13, 8, 7, 2, 11, 15, 0 });
    EXPECT_FALSE(state.move(State::Operator::Down));
  }
}

TEST(StateTest, hashFunction)
{
  auto set = std::unordered_set<State>{};
  auto state = State{ 4, 4, { 14, 12, 4, 9, 5, 10, 6, 1, 3, 13, 8, 7, 2, 11, 15, 0 } };
  set.insert(state);
  ASSERT_EQ(set.size(), 1);
  set.insert(state);
  set.insert(state);
  set.insert(state);
  set.insert(state);
  set.insert(state);
  ASSERT_EQ(set.size(), 1);
  state.move(State::Operator::Up);
  set.insert(state);
  ASSERT_EQ(set.size(), 2);

  auto hasher = std::hash<State>{};
  std::cout << "Sample hashes:\n" << std::hex;
  std::cout << "\t" << hasher(State{ 4, 4, { 14, 12, 4, 9, 5, 10, 6, 1, 3, 13, 8, 7, 2, 11, 15, 0 } })
            << '\n';
  std::cout << "\t" << hasher(State{ 4, 4, { 14, 12, 4, 9, 5, 10, 6, 1, 3, 13, 8, 7, 2, 11, 0, 15 } })
            << '\n';
  std::cout << "\t" << hasher(State{ 4, 4, { 14, 12, 4, 9, 5, 10, 6, 1, 3, 13, 8, 7, 2, 0, 11, 15 } })
            << '\n';
  std::cout << "\t" << hasher(State{ 4, 4, { 14, 12, 4, 9, 5, 10, 6, 1, 3, 13, 8, 7, 0, 11, 15, 2 } })
            << '\n';
  std::cout << "\t" << hasher(State{ 4, 4, { 14, 12, 4, 9, 5, 10, 6, 1, 3, 13, 8, 0, 2, 11, 15, 7 } })
            << std::endl;
};
