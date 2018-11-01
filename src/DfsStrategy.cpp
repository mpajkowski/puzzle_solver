#include "DfsStrategy.hpp"
#include "Node.hpp"
#include "State.hpp"
#include "StrategyContext.hpp"
#include <stack>
#include <unordered_set>

constexpr auto MAX_RECURSION_DEPTH{ 20 };

using NodeT = Node<std::string>;

DfsStrategy::DfsStrategy(std::vector<State::Operator> const& order)
  : order{ order }
{
  std::reverse(std::begin(this->order), std::end(this->order));
}

auto DfsStrategy::findSolution(StrategyContext&& strategyContext) -> Solution
{
  auto t1 = Clock::now();
  auto hasher = std::hash<State>{};

  auto initialState = strategyContext.getInitialState();
  auto const& goalState = strategyContext.getGoalState();

  if (*initialState == goalState) {
    return { "", 0, 0, 0, std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1) };
  }

  auto frontier = std::stack<std::shared_ptr<NodeT>>{};
  auto explored = std::unordered_set<std::size_t>{};

  auto root = std::make_shared<NodeT>(nullptr, initialState, "", 0);
  auto goal = std::shared_ptr<NodeT>{ nullptr };
  frontier.push(root);

  while (!frontier.empty()) {
    auto currentNode = frontier.top();
    auto currentState = currentNode->getState();

    if (*currentState == goalState) {
      goal = std::make_shared<NodeT>(*currentNode);
      break;
    }

    auto currentStateHash = hasher(*currentState);
    if (explored.find(currentStateHash) != std::end(explored)) {
      frontier.pop();
      continue;
    }
    explored.insert(currentStateHash);

    for (State::Operator op : order) {
      auto newState = std::make_shared<State>(*currentState);
      auto moveExists = newState->move(op);

      if (moveExists) {
        auto currentRecursionDepth = currentNode->getRecursionDepth();

        if (currentRecursionDepth + 1 < MAX_RECURSION_DEPTH) {
          auto path = currentNode->getOp();

          path += static_cast<std::underlying_type<State::Operator>::type>(moveExists.value());
          frontier.push(std::make_shared<NodeT>(nullptr, newState, path, currentRecursionDepth + 1));
        }
      }
    }
  }

  auto operatorStr = goal->getOp();

  return { operatorStr,
           explored.size(),
           0,
           0,
           std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1) };
}
