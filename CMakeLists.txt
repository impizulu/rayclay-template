cmake_minimum_required(VERSION 3.21)

project(app LANGUAGES C)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(rayclay
    GIT_REPOSITORY https://github.com/impizulu/rayclay.git
    GIT_TAG        main)
FetchContent_MakeAvailable(rayclay)

add_executable(app main.c)

set_target_properties(app PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON)

target_include_directories(app PRIVATE src)
target_link_libraries(app PRIVATE rayclay::rayclay)
