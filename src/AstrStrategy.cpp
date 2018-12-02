#include "AstrStrategy.hpp"
#include "Node.hpp"
#include "State.hpp"
#include "StrategyContext.hpp"
#include <iostream>
#include <numeric>
#include <queue>
#include <unordered_set>

using NodeT = Node<std::string>;
using NodeSP = std::shared_ptr<NodeT>;

AstrStrategy::AstrStrategy(StrategyContext strategyContext, Constants::Heuristic heuristic)
  : Strategy(std::move(strategyContext))
  , heuristicFn{ nullptr }
{
  using std::placeholders::_1;

  if (heuristic == Constants::Heuristic::HAMM) {
    heuristicFn = std::bind(&AstrStrategy::hamming, this, _1);
  } else {
    heuristicFn = std::bind(&AstrStrategy::manhattan, this, _1);

    auto& goalState = this->strategyContext.getGoalState();
    for (std::size_t i = 0; i < goalState.getBoard().size(); ++i) {
      goalCache[i] = goalState.getCoordinates(i);
    }
  }
}

auto AstrStrategy::findSolution() -> Solution
{
  auto t1 = Clock::now();
  auto hasher = std::hash<State>{};

  auto initialState = strategyContext.getInitialState();
  auto const& goalState = strategyContext.getGoalState();

  if (*initialState == goalState) {
    return { "", 0, 0, 0, std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1) };
  }

  auto compare = [&](NodeSP const& lhs, NodeSP const& rhs) {
    return heuristicFn(*(lhs->getState())) >= heuristicFn(*(rhs->getState()));
  };

  auto frontier = std::priority_queue<NodeSP, std::deque<NodeSP>, decltype(compare)>{ compare };
  auto explored = std::unordered_set<std::size_t>{};

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
    if (explored.find(currentStateHash) != std::end(explored)) {
      continue;
    }

    // order is not a concern here
    auto moves = {
      State::Operator::Left, State::Operator::Right, State::Operator::Up, State::Operator::Down
    };

    for (auto dir : moves) {
      auto newState = std::make_shared<State>(*currentState);
      auto moveExists = newState->move(dir);

      if (moveExists) {
        auto path = currentNode->getPayload();
        path += static_cast<std::underlying_type<State::Operator>::type>(moveExists.value());
        frontier.push(std::make_shared<NodeT>(newState, path));
      }
    }

    explored.insert(currentStateHash);
  }

  return { goal ? goal->getPayload() : "notfound",
           explored.size(),
           0,
           0,
           std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1) };
}

auto AstrStrategy::hamming(State const& currentState) -> State::ValueType
{
  auto result = State::ValueType{};

  for (std::size_t i = 0; i < currentState.getBoard().size(); ++i) {
    if (currentState.getBoard()[i] != 0) {
      if (currentState.getBoard()[i] != strategyContext.getGoalState().getBoard()[i]) {
        ++result;
      }
    }
  }

  return result;
}

auto AstrStrategy::manhattan(State const& currentState) -> State::ValueType
{
  auto result = State::ValueType{};

  for (std::size_t i = 0; i < currentState.getBoard().size(); ++i) {
    if (currentState.getBoard()[i] != 0) {
      if (currentState.getBoard()[i] != strategyContext.getGoalState().getBoard()[i]) {
        auto currCoordinates = currentState.getCoordinates(i);
        auto& goalCoordinates = goalCache.at(i);
        result += abs(goalCoordinates.x - currCoordinates.x) + abs(goalCoordinates.y - currCoordinates.y);
      }
    }
  }

  return result;
}
