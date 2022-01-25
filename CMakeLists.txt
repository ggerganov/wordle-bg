cmake_minimum_required (VERSION 3.10)
project(wordle)

set(OpenGL_GL_PREFERENCE "GLVND")

enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS "on")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(cmake/GitVars.cmake)
include(cmake/BuildTypes.cmake)

if (EMSCRIPTEN)
    option(WORDLE_WASM_SINGLE_FILE "wordle: embed WASM inside the generated wordle.js" ON)
else()
    if (MINGW)
        set(BUILD_SHARED_LIBS_DEFAULT OFF)
    else()
        set(BUILD_SHARED_LIBS_DEFAULT ON)
    endif()
endif()

# options

option(WORDLE_ALL_WARNINGS            "wordle: enable all compiler warnings" ON)
option(WORDLE_ALL_WARNINGS_3RD_PARTY  "wordle: enable all compiler warnings in 3rd party libs" OFF)

option(WORDLE_SANITIZE_THREAD         "wordle: enable thread sanitizer" OFF)
option(WORDLE_SANITIZE_ADDRESS        "wordle: enable address sanitizer" OFF)
option(WORDLE_SANITIZE_UNDEFINED      "wordle: enable undefined sanitizer" OFF)

# sanitizers

if (WORDLE_SANITIZE_THREAD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=thread")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
endif()

if (WORDLE_SANITIZE_ADDRESS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
endif()

if (WORDLE_SANITIZE_UNDEFINED)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=undefined")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
endif()

# dependencies

if (EMSCRIPTEN)
    set(CMAKE_CXX_FLAGS " \
    -s USE_SDL=2 \
    -s DISABLE_EXCEPTION_CATCHING=1 \
    ")

    set(CMAKE_EXE_LINKER_FLAGS " \
    --bind \
    --use-preload-cache \
    --closure 1 \
    -s ALLOW_MEMORY_GROWTH=1 \
    -s NO_EXIT_RUNTIME=0 \
    ")
else()
    find_package(SDL2 REQUIRED)
    string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
endif()

add_subdirectory(third-party)

# main

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo")
endif ()

add_subdirectory(src)
