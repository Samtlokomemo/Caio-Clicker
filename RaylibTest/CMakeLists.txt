cmake_minimum_required(VERSION 3.14)

project(RaylibTest VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(raylib)

add_executable(RaylibTest
        main.cpp
        Game.cpp
        GameData.cpp
        ClickerButton.cpp
        FloatingText.cpp
        Item.cpp
        Timer.cpp
        Upgrade.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
