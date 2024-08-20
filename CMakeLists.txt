cmake_minimum_required(VERSION 3.29)
project(orderbook)

set(CMAKE_CXX_STANDARD 20)

add_executable(orderbook main.cpp
        Orderbook.cpp
        Orderbook.h)
