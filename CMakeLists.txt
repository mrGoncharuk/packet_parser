cmake_minimum_required(VERSION 3.15)
project(packet_parser)

set(CMAKE_CXX_STANDARD 11)

add_executable(packet_parser src/main.cpp src/PacketParser.cpp includes/PacketParser.hpp includes/Exceptions.hpp src/Exceptions.cpp src/AList.cpp)