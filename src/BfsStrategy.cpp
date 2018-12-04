#include "BfsStrategy.hpp"
#include "Node.hpp"
#include "State.hpp"
#include "StrategyContext.hpp"
#include <algorithm>
#include <iostream>
#include <memory>
#include <queue>
#include <unordered_set>

BfsStrategy::BfsStrategy(StrategyContext strategyContext, std::vector<State::Operator> const& order)
  : Strategy(std::move(strategyContext))
  , order{ order }
{}

auto BfsStrategy::findSolution() -> Solution
{
  auto t1 = Clock::now();
  auto hasher = std::hash<State>{};

  auto initialState = strategyContext.getInitialState();
  auto const& goalState = strategyContext.getGoalState();

  if (*initialState == goalState) {
    return { "", 0, 0, 0, std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1) };
  }

  std::uint8_t maxRecursionDepth{};
  std::uint64_t processedCounter{};

  auto frontier = std::queue<std::shared_ptr<Node>>{};
  auto explored = std::unordered_set<std::size_t>{};

  auto root = std::make_shared<Node>(initialState);
  auto goal = std::shared_ptr<Node>{ nullptr };
  frontier.push(root);

  while (!frontier.empty()) {
    auto currNode = frontier.front();
    auto currentState = currNode->getState();
    auto currRecursionDepth = currNode->getCurrentRecursionDepth();

    if (currRecursionDepth > maxRecursionDepth) {
      maxRecursionDepth = currRecursionDepth;
    }

    ++processedCounter;

    frontier.pop();

    if (*currentState == goalState) {
      goal = std::make_shared<Node>(*currNode);
      break;
    }

    auto currentStateHash = hasher(*currentState);
    if (explored.find(currentStateHash) != std::end(explored)) {
      continue;
    }

    for (State::Operator op : order) {
      auto newState = std::make_shared<State>(*currentState);
      auto moveExists = newState->move(op);

      if (moveExists) {
        frontier.push(std::make_shared<Node>(newState, currNode, op, currRecursionDepth + 1));
      }
    }
    explored.insert(currentStateHash);
  }

  auto operatorStr = std::string{};

  if (goal) {
    for (auto it = goal; it->getParent() != nullptr; it = it->getParent()) {
      auto currentOp = it->getOp().value();
      operatorStr += static_cast<char>(currentOp);
    }
  } else {
    operatorStr = "notfound";
  }

  std::reverse(std::begin(operatorStr), std::end(operatorStr));

  return { operatorStr,
           explored.size(),
           processedCounter - explored.size(),
           maxRecursionDepth,
           std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1) };
}
