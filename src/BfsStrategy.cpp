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

using NodeT = Node<std::optional<State::Operator>>;

auto BfsStrategy::findSolution(StrategyContext&& strategyContext) -> Solution
{
  auto t1 = Clock::now();
  auto hasher = std::hash<State>{};

  auto initialState = strategyContext.getInitialState();
  auto const& goalState = strategyContext.getGoalState();

  if (*initialState == goalState) {
    return { "", 0, 0, 0, std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1) };
  }

  auto frontier = std::queue<std::shared_ptr<NodeT>>{};
  auto explored = std::unordered_set<std::size_t>{};

  auto root = std::make_shared<NodeT>(nullptr, initialState, std::nullopt);
  auto goal = std::shared_ptr<NodeT>{ nullptr };
  frontier.push(root);

  while (!frontier.empty()) {
    auto currNode = frontier.front();
    auto currentState = currNode->getState();
    frontier.pop();

    if (*currentState == goalState) {
      goal = std::make_shared<NodeT>(*currNode);
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
        frontier.push(std::make_shared<NodeT>(currNode, newState, op));
      }
    }

    explored.insert(currentStateHash);
  }

  auto operatorStr = std::string{};

  for (auto it = goal; goal->getParent() != nullptr; goal = goal->getParent()) {
    auto currentOp = goal->getPayload().value();

    operatorStr += static_cast<std::underlying_type<State::Operator>::type>(currentOp);
  }

  std::reverse(std::begin(operatorStr), std::end(operatorStr));

  return { operatorStr,
           explored.size(),
           0,
           0,
           std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1) };
}
