#include "ConfigParser.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <string>

TEST(ConfigTest, firstInvocation)
{
  const char* argv[] = {
    "program",
    "bfs",
    "RDUL",
    "4x4_01_0001.txt",
    "4x4_01_0001_bfs_rdul_sol.txt",
    "4x4_01_0001_bfs_rdul_stats.txt",
  };

  int argc = 6;
  auto configParser = ConfigParser{ argc, const_cast<char**>(argv) };
  auto config = configParser.createConfig();

  EXPECT_EQ(config.strategy, Constants::Strategy::BFS);
  EXPECT_EQ(std::get<std::string>(config.strategyParam), "RDUL");
  EXPECT_EQ(config.firstStateFileName, "4x4_01_0001.txt");
  EXPECT_EQ(config.solutionFileName, "4x4_01_0001_bfs_rdul_sol.txt");
  EXPECT_EQ(config.additionalInfoFileName, "4x4_01_0001_bfs_rdul_stats.txt");
}

TEST(ConfigTest, secondInvocation)
{
  const char* argv[] = {
    "program",
    "dfs",
    "LUDR",
    "4x4_01_0001.txt",
    "4x4_01_0001_dfs_ludr_sol.txt",
    "4x4_01_0001_dfs_ludr_stats.txt",
  };

  int argc = 6;
  auto configParser = ConfigParser{ argc, const_cast<char**>(argv) };
  auto config = configParser.createConfig();

  EXPECT_EQ(config.strategy, Constants::Strategy::DFS);
  EXPECT_EQ(std::get<std::string>(config.strategyParam), "LUDR");
  EXPECT_EQ(config.firstStateFileName, "4x4_01_0001.txt");
  EXPECT_EQ(config.solutionFileName, "4x4_01_0001_dfs_ludr_sol.txt");
  EXPECT_EQ(config.additionalInfoFileName, "4x4_01_0001_dfs_ludr_stats.txt");
}

TEST(ConfigTest, thirdInvocation)
{
  const char* argv[] = {
    "program",
    "astr",
    "manh",
    "4x4_01_0001.txt",
    "4x4_01_0001_astr_manh_sol.txt",
    "4x4_01_0001_astr_manh_stats.txt",
  };

  int argc = 6;
  auto configParser = ConfigParser{ argc, const_cast<char**>(argv) };
  auto config = configParser.createConfig();

  EXPECT_EQ(config.strategy, Constants::Strategy::ASTR);
  EXPECT_EQ(std::get<Constants::Heuristic>(config.strategyParam), Constants::Heuristic::MANH);
  EXPECT_EQ(config.firstStateFileName, "4x4_01_0001.txt");
  EXPECT_EQ(config.solutionFileName, "4x4_01_0001_astr_manh_sol.txt");
  EXPECT_EQ(config.additionalInfoFileName, "4x4_01_0001_astr_manh_stats.txt");
}
