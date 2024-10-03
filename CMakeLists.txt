cmake_minimum_required(VERSION 3.28)
project(docking-sim LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

file(GLOB CPP_H
     "src/main.cpp"
     "includes/window/window.h"
     "src/window/window.cpp"
     "includes/window/settings.h"
     "src/window/settings.cpp"
     "includes/window/simulation.h"
     "src/window/simulation.cpp"
     "includes/window/conclusion.h"
     "src/window/conclusion.cpp"
     "includes/ship/ship.h"
     "src/ship/ship.cpp"
     "includes/ship/cargo_ship.h"
     "src/ship/cargo_ship.cpp"
     "includes/ship/tanker.h"
     "src/ship/tanker.cpp"
     "includes/crane/crane.h"
     "src/crane/crane.cpp"
     "includes/crane/bulk_crane.h"
     "src/crane/bulk_crane.cpp"
     "includes/crane/fluid_crane.h"
     "src/crane/fluid_crane.cpp"
     "includes/crane/container_crane.h"
     "src/crane/container_crane.cpp"
     "includes/cursor_hover_window.h"
     "src/cursor_hover_window.cpp"
     "includes/constants.h"
)

add_executable(main ${CPP_H})
target_link_libraries(main PRIVATE sfml-graphics)
target_link_libraries(main PRIVATE sfml-window)
target_link_libraries(main PRIVATE sfml-system)
target_compile_features(main PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()
