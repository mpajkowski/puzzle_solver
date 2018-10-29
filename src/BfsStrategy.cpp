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

BfsStrategy::BfsStrategy(std::string const& order)
  : order{}
{
  // TODO move that somewhere
  // probably it should be moved to StateParse class
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
  auto explored = std::unordered_set<std::shared_ptr<State>>{};

  auto root = std::make_shared<Node>(nullptr, initialState);
  auto goal = std::shared_ptr<Node>{ nullptr };
  frontier.push(root);

  while (!frontier.empty()) {
    auto& currNode = frontier.front();
    auto currState = currNode->getState();

    if (*currState == goalState) {
      goal = std::make_shared<Node>(*currNode);
      break;
    }

    if (explored.find(currState) != std::end(explored)) {
      continue;
    }

    for (State::Operator op : order) {
      auto newState = std::make_shared<State>(*currState);
      auto moveExists = newState->move(op);
      if (moveExists) {
        frontier.push(std::make_shared<Node>(currNode, newState, op));
      }
    }

    frontier.pop();
    explored.insert(currState);
  }

  auto operatorStr = std::string{};

  for (auto it = goal; goal->getParent() != nullptr; goal = goal->getParent()) {
    operatorStr += static_cast<std::underlying_type<State::Operator>::type>(goal->getOp().value());
  }

  std::reverse(std::begin(operatorStr), std::end(operatorStr));

  return { operatorStr,
           explored.size(),
           0,
           0,
           std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1) };
}
