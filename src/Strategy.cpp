#include "Strategy.hpp"
#include "Node.hpp"

Strategy::Strategy(StrategyContext strategyContext)
  : strategyContext{ std::move(strategyContext) }
{}

auto Strategy::constructPath(std::shared_ptr<Node> const& goal) -> std::string
{
  auto operatorStr = std::string{};

  for (auto it = goal; it->getParent() != nullptr; it = it->getParent()) {
    auto currentOp = it->getOp().value();
    operatorStr += static_cast<char>(currentOp);
  }

  std::reverse(std::begin(operatorStr), std::end(operatorStr));
  return operatorStr;
}
