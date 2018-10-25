#include "State.hpp"
#include "StrategyContext.hpp"
#include <gtest/gtest.h>

TEST(StrategyTest, creationWantedState)
{
  auto state = State{ 4, 4, { 9, 12, 4, 1, 5, 10, 6, 0, 3, 13, 8, 7, 14, 2, 11, 15 } };
  auto context = StrategyContext{ state };

  ASSERT_EQ(context.getWantedState(), State(4, 4, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0 }));
}
