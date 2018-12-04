#include "DfsStrategy.hpp"
#include "Node.hpp"
#include "State.hpp"
#include "StrategyContext.hpp"
#include <stack>
#include <unordered_set>

constexpr std::uint8_t MAX_RECURSION_DEPTH{ 20 };

DfsStrategy::DfsStrategy(StrategyContext strategyContext, std::vector<State::Operator> const& order)
  : Strategy(std::move(strategyContext))
  , order{ order }
{
  std::reverse(std::begin(this->order), std::end(this->order));
}

auto DfsStrategy::findSolution() -> Solution
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

  auto frontier = std::list<std::shared_ptr<Node>>{};
  auto explored = std::unordered_set<std::size_t>{};

  auto root = std::make_shared<Node>(initialState);
  auto goal = std::shared_ptr<Node>{ nullptr };
  frontier.push_back(root);

  while (!frontier.empty()) {
    auto currentNode = frontier.back();
    auto currentState = currentNode->getState();

    auto currentRecursionDepth = currentNode->getCurrentRecursionDepth();

    ++processedCounter;
    frontier.pop_back();

    if (currentRecursionDepth > MAX_RECURSION_DEPTH) {
      continue;
    }

    if (currentRecursionDepth > maxRecursionDepth) {
      maxRecursionDepth = currentRecursionDepth;
    }

    if (*currentState == goalState) {
      goal = std::make_shared<Node>(*currentNode);
      break;
    }

    for (State::Operator op : order) {
      auto newState = std::make_shared<State>(*currentState);
      auto moveExists = newState->move(op);

      if (moveExists) {
        auto newNode = std::make_shared<Node>(newState, currentNode, op, currentRecursionDepth + 1);

        if (std::find(std::begin(frontier), std::end(frontier), newNode) == std::end(frontier) &&
            explored.find(hasher(*newState)) == std::end(explored)) {
          frontier.emplace_back(std::move(newNode));
        }
      }
    }
    explored.insert(hasher(*currentState));
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
