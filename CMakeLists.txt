cmake_minimum_required(VERSION 3.23)

project(MiddleCore)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_executable(MiddleCore)

target_sources(MiddleCore
  PRIVATE
    src/main.cpp
)

target_link_libraries(MiddleCore PRIVATE glfw glad::glad)