#include "Strategy.hpp"
#include <gtest/gtest.h>

class EatAndLiveTestStrategy : public Strategy
{
public:
  EatAndLiveTestStrategy(State state)
    : Strategy{ state }
  {}

  auto findSolution() -> Solution
  {
    auto operatedState = getOperatedState();
    auto wantedState = getWantedState();

    EXPECT_EQ(operatedState.getCol(), wantedState.getCol());
    EXPECT_EQ(operatedState.getRow(), wantedState.getRow());

    auto wantWantedToBe = State{ 4, 4, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0 } };

    EXPECT_EQ(wantedState, wantWantedToBe);

    return {};
  }
};

TEST(StrategyTest, initialization)
{
  auto state = State(4, 4, { 9, 12, 4, 1, 5, 10, 6, 0, 3, 13, 8, 7, 14, 2, 11, 15 });
  auto eal = EatAndLiveTestStrategy{ std::move(state) };

  // trigger to evaluate test results
  eal.findSolution();
}
