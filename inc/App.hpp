#pragma once
#include "Config.hpp"
#include <memory>

class Strategy;

class App
{
public:
  App(Config config);
  auto run() -> void;

private:
  auto init() -> void;
  std::unique_ptr<Strategy> strategy;
  Config config;
};
