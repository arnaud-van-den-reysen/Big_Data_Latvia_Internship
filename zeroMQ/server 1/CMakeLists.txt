cmake_minimum_required(VERSION 2.8)
project(b3d)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Werror=vla  -O2 -DNDEBUG -Wall -Wall -g -Wextra -Wno-sign-compare -frounding-math -lzmq")

include_directories("${CMAKE_SOURCE_DIR}/include")

add_subdirectory(src)
