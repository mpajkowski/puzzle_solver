#include "AstrStrategy.hpp"
#include "Node.hpp"
#include "State.hpp"
#include "StrategyContext.hpp"
#include <iostream>
#include <numeric>
#include <set>
#include <unordered_set>

using NodeSP = std::shared_ptr<Node>;

AstrStrategy::AstrStrategy(StrategyContext strategyContext, Constants::Heuristic heuristic)
  : Strategy(std::move(strategyContext))
  , heuristicFn{ nullptr }
{
  using std::placeholders::_1;

  if (heuristic == Constants::Heuristic::HAMM) {
    heuristicFn = std::bind(&AstrStrategy::hamming, this, _1);
  } else {
    heuristicFn = std::bind(&AstrStrategy::manhattan, this, _1);
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

  std::uint8_t maxRecursionDepth{};
  std::uint64_t processedCounter{};

  auto compare = [&](NodeSP const& lhs, NodeSP const& rhs) {
    return heuristicFn(*(lhs->getState())) < heuristicFn(*(rhs->getState()));
  };

  auto frontier = std::multiset<NodeSP, decltype(compare)>{ compare };
  auto explored = std::unordered_set<std::size_t>{};

  auto root = std::make_shared<Node>(initialState);
  auto goal = std::shared_ptr<Node>{ nullptr };
  frontier.insert(root);

  while (!frontier.empty()) {
    auto currentNode = *std::begin(frontier);
    auto currentState = currentNode->getState();

    auto currentRecursionDepth = currentNode->getCurrentRecursionDepth();

    if (currentRecursionDepth > maxRecursionDepth) {
      maxRecursionDepth = currentRecursionDepth;
    }

    ++processedCounter;
    frontier.erase(std::begin(frontier));

    if (*currentState == goalState) {
      goal = std::make_shared<Node>(*currentNode);
      break;
    }

    // order is not a concern here
    auto moves = {
      State::Operator::Left, State::Operator::Right, State::Operator::Up, State::Operator::Down
    };

    for (auto dir : moves) {
      auto newState = std::make_shared<State>(*currentState);
      auto moveExists = newState->move(dir);

      if (moveExists) {
        auto newNode = std::make_shared<Node>(newState, currentNode, dir, currentRecursionDepth + 1);

        bool foundInExplored = explored.find(hasher(*newState)) != std::end(explored);
        bool foundInFrontier = std::find_if(std::begin(frontier), std::end(frontier), [&](auto const& elem) {
                                 return elem->getState() == newNode->getState();
                               }) != std::end(frontier);

        if (!foundInExplored && !foundInFrontier) {
          frontier.emplace(std::move(newNode));
        }
      }

      explored.insert(hasher(*currentState));
    }
  }

  auto operatorStr = goal ? std::optional(constructPath(goal)) : std::nullopt;

  return { operatorStr,
           explored.size() + frontier.size(),
           explored.size(),
           maxRecursionDepth,
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

  for (int x = 0; x < currentState.getRow(); x++) {
    for (int y = 0; y < currentState.getCol(); y++) {
      int value = currentState.getBoard()[y + currentState.getCol() * x];
      if (value != 0) {
        int targetX = (value - 1) / currentState.getCol();
        int targetY = (value - 1) % currentState.getCol();
        int dx = x - targetX;
        int dy = y - targetY;
        result += abs(dx) + abs(dy);
      }
    }
  }

  return result;
}
