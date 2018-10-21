set(src_files Node.cpp Config.cpp ConfigParser.cpp Constants.cpp State.cpp StateParser.cpp)
add_library(${proj_name}_lib ${src_files})
add_executable(${proj_name} main.cpp)
target_link_libraries(${proj_name} ${proj_name}_lib)
