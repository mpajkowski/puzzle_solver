set(src_files
  AstrStrategy.cpp
  App.cpp
  BfsStrategy.cpp
  Config.cpp
  ConfigParser.cpp
  Constants.cpp
  DfsStrategy.cpp
  ResultsManager.cpp
  State.cpp
  StateParser.cpp
  Strategy.cpp
  StrategyContext.cpp)

add_library(${proj_name}_lib ${src_files})
add_executable(${proj_name} main.cpp)
target_link_libraries(${proj_name} ${proj_name}_lib)

find_package(Boost)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

add_custom_command(TARGET ${proj_name}
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${proj_name}> ${PROJECT_SOURCE_DIR}/sandbox)
