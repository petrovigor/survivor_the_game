cmake_minimum_required(VERSION 3.12)
project(survivor CXX)

if(NOT WIN32)
  message(FATAL_ERROR "Only Windows builts are allowed. WinAPI used")
endif()

add_subdirectory(modules/city_road_gen)
add_subdirectory(modules/game)
