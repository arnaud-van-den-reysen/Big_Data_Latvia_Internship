
set(MAIN_INCLUDE
  server.cpp
)


find_package(cppzmq REQUIRED)
include_directories(${cppzmq_INCLUDE_DIR})
include_directories(${cppzmq_LIBRARY})

message(STATUS ${ZMQ_INCLUDE_DIRS})
add_executable(main ${MAIN_INCLUDE})

target_link_libraries(main ${cppzmq_LIBRARY})
