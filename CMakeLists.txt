cmake_minimum_required(VERSION 3.15)
project(PacketParser)

set(CMAKE_CXX_STANDARD 11)

add_executable(PacketParser src/main.cpp src/PacketParser.cpp includes/PacketParser.hpp)