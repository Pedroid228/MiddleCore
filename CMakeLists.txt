cmake_minimum_required(VERSION 3.23)

project(MiddleCore)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_executable(MiddleCore)

target_sources(MiddleCore
  PRIVATE
    src/main.cpp
)

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT MiddleCore)
set_target_properties(MiddleCore PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

target_link_libraries(MiddleCore PRIVATE glfw glad::glad)

add_custom_command(TARGET MiddleCore POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/assets" "$<TARGET_FILE_DIR:MiddleCore>/assets")