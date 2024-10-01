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
     "src/window/window.h"
     "src/window/window.cpp"
     "src/window/settings.h"
     "src/window/settings.cpp"
     "src/window/simulation.h"
     "src/window/simulation.cpp"
     "src/window/conclusion.h"
     "src/window/conclusion.cpp"
     "src/ship/Ship.h"
     "src/ship/Ship.cpp"
     "src/ship/CargoShip.h"
     "src/ship/CargoShip.cpp"
     "src/ship/Tanker.h"
     "src/ship/Tanker.cpp"
     "src/crane/crane.h"
     "src/crane/crane.cpp"
     "src/crane/bulk_crane.h"
     "src/crane/bulk_crane.cpp"
     "src/crane/fluid_crane.h"
     "src/crane/fluid_crane.cpp"
     "src/crane/container_crane.h"
     "src/crane/container_crane.cpp"
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
