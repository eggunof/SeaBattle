cmake_minimum_required(VERSION 3.25)
project(SeaBattle)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE CCFILES "src/*.cc")
file(GLOB_RECURSE HFILES "src/*.h")
add_executable(${PROJECT_NAME} ${CCFILES} ${HFILES})

find_package(nlohmann_json QUIET)

if (NOT nlohmann_json_FOUND)
    message(STATUS "nlohmann_json not found, using FetchContent to load it...")

    include(FetchContent)
    FetchContent_Declare(
            nlohmann_json
            GIT_REPOSITORY https://github.com/nlohmann/json.git
            GIT_TAG v3.11.3
    )
    FetchContent_MakeAvailable(nlohmann_json)
endif ()

target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)