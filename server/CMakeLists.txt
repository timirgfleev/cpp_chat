cmake_minimum_required(VERSION 3.5)
project(qt_chat_server)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost 1.58.0 REQUIRED COMPONENTS system)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(server server.cpp)

target_link_libraries(server ${Boost_LIBRARIES})