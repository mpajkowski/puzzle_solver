#include "BfsStrategy.hpp"
#include "Node.hpp"
#include "State.hpp"
#include "StrategyContext.hpp"
#include <algorithm>
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>

BfsStrategy::BfsStrategy(std::string const& order)
  : order{}
{
  // map 'raw' char operators to typesafe operators
  for (char ch : order) {
    switch (ch) {
      case 'L':
        this->order.push_back(State::Operator::Left);
        break;
      case 'R':
        this->order.push_back(State::Operator::Right);
        break;
      case 'U':
        this->order.push_back(State::Operator::Up);
        break;
      case 'D':
        this->order.push_back(State::Operator::Down);
        break;
      default:
        throw std::invalid_argument{ "wrong char for move sequence" };
    }
  }
}

auto BfsStrategy::findSolution(StrategyContext&& strategyContext) -> Solution
{
  auto t1 = Clock::now();

  auto initialState = strategyContext.getInitialState();
  auto const& goalState = strategyContext.getGoalState();

  if (*initialState == goalState) {
    return { "", 0, 0, 0, std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1) };
  }

  auto frontier = std::queue<std::shared_ptr<Node>>{};
  auto explored = std::unordered_set<State>{};

  frontier.push(std::make_shared<Node>(nullptr, initialState));

  while (!frontier.empty()) {
    auto& currNode = frontier.front();
    auto& currState = *currNode->getState();

    if (currState == goalState)
      break;
    // finished right here
    for (State::Operator it : order) {
      currState.move(it);
    }

    frontier.pop();
  }

  auto operatorStr = std::string{};
  std::uint64_t visitedStatesCount{};
  std::uint64_t processedStatesCount{};

  return { operatorStr,
           visitedStatesCount,
           processedStatesCount,
           0,
           std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1) };
}
