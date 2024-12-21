cmake_minimum_required(VERSION 3.25)
project(SeaBattle)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE CCFILES "src/*.cc")
file(GLOB_RECURSE HFILES "src/*.h")
add_executable(${PROJECT_NAME} ${CCFILES} ${HFILES})

find_package(nlohmann_json 3.2.0 REQUIRED)

target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)