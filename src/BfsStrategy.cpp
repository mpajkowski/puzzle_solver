#include "BfsStrategy.hpp"
#include "Node.hpp"
#include "State.hpp"
#include "StrategyContext.hpp"
#include <algorithm>
#include <iostream>
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>

BfsStrategy::BfsStrategy(std::vector<State::Operator> const& order)
  : order{ order }
{}

auto BfsStrategy::findSolution(StrategyContext&& strategyContext) -> Solution
{
  auto t1 = Clock::now();
  auto hasher = std::hash<State>{};

  auto initialState = strategyContext.getInitialState();
  auto const& goalState = strategyContext.getGoalState();

  if (*initialState == goalState) {
    return { "", 0, 0, 0, std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1) };
  }

  auto frontier = std::queue<std::shared_ptr<Node>>{};
  auto explored = std::unordered_set<std::size_t>{};

  auto root = std::make_shared<Node>(nullptr, initialState);
  auto goal = std::shared_ptr<Node>{ nullptr };
  frontier.push(root);

  while (!frontier.empty()) {
    auto& currNode = frontier.front();
    auto currentState = currNode->getState();

    if (*currentState == goalState) {
      goal = std::make_shared<Node>(*currNode);
      break;
    }

    auto currentStateHash = hasher(*currentState);
    if (explored.find(currentStateHash) != std::end(explored)) {
      frontier.pop();
      continue;
    }

    for (State::Operator op : order) {
      auto newState = std::make_shared<State>(*currentState);
      auto moveExists = newState->move(op);
      if (moveExists) {
        frontier.push(std::make_shared<Node>(currNode, newState, op));
      }
    }

    frontier.pop();
    explored.insert(currentStateHash);
  }

  auto operatorStr = std::string{};

  for (auto it = goal; it->getParent() != nullptr; it = it->getParent()) {
    auto currentOp = goal->getOp().value();
    operatorStr += static_cast<std::underlying_type<State::Operator>::type>(currentOp);
  }

  std::reverse(std::begin(operatorStr), std::end(operatorStr));

  return { operatorStr,
           explored.size(),
           0,
           0,
           std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1) };
}
