#include "DfsStrategy.hpp"
#include "Node.hpp"
#include "State.hpp"
#include "StrategyContext.hpp"
#include <stack>
#include <unordered_map>

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
    return { "", 0, 0, 0, (Clock::now() - t1) };
  }

  std::uint8_t maxRecursionDepth{};
  std::uint64_t processedCounter{};

  auto frontier = std::list<std::shared_ptr<Node>>{};
  auto explored = std::unordered_map<std::size_t, std::uint8_t>{};

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

    auto currentStateHash = hasher(*currentState);

    if (auto occurence = explored.find(currentStateHash); occurence != std::end(explored)) {
      if (occurence->second < currentRecursionDepth) {
        continue;
      } else {
        occurence->second = currentRecursionDepth;
      }
    }
    explored[currentStateHash] = currentRecursionDepth;

    for (State::Operator op : order) {
      auto newState = std::make_shared<State>(*currentState);
      auto moveExists = newState->move(op);

      if (moveExists) {
        auto newNode = std::make_shared<Node>(newState, currentNode, op, currentRecursionDepth + 1);

        auto exploredOccurence = explored.find(hasher(*newState));

        if (exploredOccurence != std::end(explored)) {
          auto newNodeCurrRecursionDepth = newNode->getCurrentRecursionDepth();
          if (exploredOccurence->second < newNodeCurrRecursionDepth) {
            // nothing to do here; just found an occurence thus need to step out
            continue;
          } else {
            exploredOccurence->second = newNodeCurrRecursionDepth;
          }
        }

        auto frontierOccurence =
          std::find_if(std::begin(frontier), std::end(frontier), [&](auto const& elem) {
            return elem->getState() == newNode->getState();
          });

        if (frontierOccurence != std::end(frontier)) {
          auto newNodeCurrRecursionDepth = newNode->getCurrentRecursionDepth();
          if ((*frontierOccurence)->getCurrentRecursionDepth() < newNodeCurrRecursionDepth) {
            // nothing to do here; just found an occurence thus need to step out
            continue;
          } else {
            frontier.erase(frontierOccurence);
          }
        }

        frontier.emplace_back(std::move(newNode));
      }
    }
  }

  auto operatorStr = goal ? std::optional(constructPath(goal)) : std::nullopt;

  return {
    operatorStr, frontier.size() + explored.size(), explored.size(), maxRecursionDepth, (Clock::now() - t1)
  };
}
