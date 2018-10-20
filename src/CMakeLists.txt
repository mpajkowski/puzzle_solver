set(src_files Node.cpp Config.cpp ConfigParser.cpp Constants.cpp)
add_executable(${proj_name} ${src_files} main.cpp)
add_library(${proj_name}_lib ${src_files})
