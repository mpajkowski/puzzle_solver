#pragma once
#include <memory>

class State;
class Strategy;

class App
{
public:
  auto run() -> void;

private:
  std::unique_ptr<State> state;
  std::unique_ptr<Strategy> strategy;
};
