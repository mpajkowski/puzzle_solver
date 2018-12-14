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
    return { "", 0, 0, 0, (Clock::now() - t1) };
  }

  std::uint8_t maxRecursionDepth{};
  std::uint64_t processedCounter{};

  auto compare = [this](NodeSP const& lhs, NodeSP const& rhs) {
    return lhs->getCurrentRecursionDepth() + heuristicFn(*(lhs->getState())) <
           rhs->getCurrentRecursionDepth() + heuristicFn(*(rhs->getState()));
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

    frontier.erase(std::begin(frontier));
    ++processedCounter;

    if (*currentState == goalState) {
      goal = std::make_shared<Node>(*currentNode);
      break;
    }

    // order is not a concern here
    auto moves = {
      State::Operator::Up, State::Operator::Down, State::Operator::Left, State::Operator::Right
    };

    for (auto dir : moves) {
      auto newState = std::make_shared<State>(*currentState);

      if (newState->move(dir)) {
        auto newNode = std::make_shared<Node>(newState, currentNode, dir, currentRecursionDepth + 1);

        bool foundInExplored = explored.find(hasher(*newState)) != std::end(explored);
        bool foundInFrontier = std::find_if(std::begin(frontier), std::end(frontier), [&](auto const& elem) {
                                 return *(elem->getState()) == *(newNode->getState());
                               }) != std::end(frontier);

        if (!foundInExplored && !foundInFrontier) {
          frontier.emplace(std::move(newNode));
        }
      }
    }

    explored.insert(hasher(*currentState));
  }

  auto operatorStr = goal ? std::optional(constructPath(goal)) : std::nullopt;

  return {
    operatorStr, explored.size() + frontier.size(), explored.size(), maxRecursionDepth, (Clock::now() - t1)
  };
}

auto AstrStrategy::hamming(State const& currentState) -> int
{
  auto& currentBoard = currentState.getBoard();
  auto& goalBoard = strategyContext.getGoalState().getBoard();

  int result{};

  for (size_t i = 0; i < currentBoard.size(); ++i) {
    // branch prediction optimalization
    result += static_cast<int>((currentBoard[i] != goalBoard[i]) && currentBoard[i] != 0);
  }

  return result;
}

auto AstrStrategy::manhattan(State const& currentState) -> int
{
  int result{};

  for (int i = 0; i < currentState.getRow(); ++i) {
    for (int j = 0; j < currentState.getCol(); ++j) {
      int value = currentState.getBoard()[currentState.getRow() * i + j];
      if (value != 0) {
        int goalI = (value - 1) / currentState.getRow();
        int goalJ = (value - 1) % currentState.getCol();
        result += abs(i - goalI) + abs(j - goalJ);
      }
    }
  }

  return result;
}
