#include "DfsStrategy.hpp"
#include "Node.hpp"
#include "State.hpp"
#include "StrategyContext.hpp"
#include <stack>
#include <unordered_map>

constexpr std::uint8_t MAX_RECURSION_DEPTH{ 21 };

struct DFSPayload
{
  DFSPayload(std::string path = std::string{}, std::uint8_t currentRecursionDepth = 0u)
    : path{ path }
    , currentRecursionDepth{ currentRecursionDepth }
  {}

  std::string path;
  std::uint8_t currentRecursionDepth;
};

using NodeT = Node<DFSPayload>;

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
  auto explored = std::unordered_map<std::size_t, std::uint8_t>{};

  auto root = std::make_shared<NodeT>(initialState);
  auto goal = std::shared_ptr<NodeT>{ nullptr };
  frontier.push(root);

  while (!frontier.empty()) {
    auto currentNode = frontier.top();
    auto currentState = currentNode->getState();
    frontier.pop();

    if (*currentState == goalState) {
      goal = std::make_shared<NodeT>(*currentNode);
      break;
    }

    auto currentStateHash = hasher(*currentState);
    auto currentRecursionDepth = currentNode->getPayload().currentRecursionDepth;

    if (auto occurence = explored.find(currentStateHash); occurence != std::end(explored)) {
      if (occurence->second <= currentRecursionDepth) {
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
        if (currentRecursionDepth += 1; currentRecursionDepth < MAX_RECURSION_DEPTH) {
          auto path = currentNode->getPayload().path;

          path += static_cast<std::underlying_type<State::Operator>::type>(moveExists.value());
          auto payload = DFSPayload{ path, currentRecursionDepth };
          frontier.push(std::make_shared<NodeT>(newState, std::move(payload)));
        }
      }
    }
  }

  return { goal ? goal->getPayload().path : "notfound",
           explored.size(),
           0,
           0,
           std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1) };
}
