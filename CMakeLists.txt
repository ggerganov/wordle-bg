cmake_minimum_required (VERSION 3.0)
project(wordle VERSION 0.3.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS "on")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(cmake/GitVars.cmake)
include(cmake/BuildTypes.cmake)

if (EMSCRIPTEN)
    set(WORDLE_SUPPORT_SDL2_DEFAULT ON)
    set(BUILD_SHARED_LIBS_DEFAULT OFF)

    option(WORDLE_WASM_SINGLE_FILE "wordle: embed WASM inside the generated wordle.js" ON)
else()
    set(WORDLE_SUPPORT_SDL2_DEFAULT ON)
endif()

# options

option(BUILD_SHARED_LIBS              "wordle: build shared libs" ${BUILD_SHARED_LIBS_DEFAULT})
option(USE_FINDSDL2                   "wordle: use the FindSDL2.cmake script" OFF)

option(WORDLE_ALL_WARNINGS            "wordle: enable all compiler warnings" ON)
option(WORDLE_ALL_WARNINGS_3RD_PARTY  "wordle: enable all compiler warnings in 3rd party libs" ON)

option(WORDLE_SANITIZE_THREAD         "wordle: enable thread sanitizer" OFF)
option(WORDLE_SANITIZE_ADDRESS        "wordle: enable address sanitizer" OFF)
option(WORDLE_SANITIZE_UNDEFINED      "wordle: enable undefined sanitizer" OFF)

# sanitizers

if (WORDLE_SANITIZE_THREAD)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=thread")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
endif()

if (WORDLE_SANITIZE_ADDRESS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer -D_GLIBCXX_DEBUG")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer -D_GLIBCXX_DEBUG")
endif()

if (WORDLE_SANITIZE_UNDEFINED)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=undefined")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
endif()

# dependencies

if (EMSCRIPTEN)
    #-s USE_PTHREADS=1 \
    set(CMAKE_CXX_FLAGS " \
    --bind \
    -s TOTAL_MEMORY=67108864 \
    -s USE_SDL=2 \
    -s ASSERTIONS=1 \
    -s DISABLE_EXCEPTION_CATCHING=0 \
    -s 'EXTRA_EXPORTED_RUNTIME_METHODS=[\"writeArrayToMemory\"]' \
    ")

    unset(SDL2_INCLUDE_DIRS)
    unset(SDL2_LIBRARIES)
endif()

if (NOT EMSCRIPTEN)
    find_package(SDL2)

    if (NOT USE_FINDSDL2 AND NOT SDL2_FOUND)
        message(WARNING "Unable to find SDL2 library. It is either not installed or CMake cannot find it."
            " In the latter case, setting the USE_FINDSDL2 variable might help:\n"
            "   $ cmake -D USE_FINDSDL2 .."
            )

        message(FATAL_ERROR "Aborting")
    endif()

    string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)

    message(STATUS "SDL2_INCLUDE_DIRS = ${SDL2_INCLUDE_DIRS}")
    message(STATUS "SDL2_LIBRARIES = ${SDL2_LIBRARIES}")
endif()

# main

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WORDLE_ALL_WARNINGS)
    if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
    else()
        # todo : windows
    endif()
endif()

# third-party

add_subdirectory(third-party)

# main

add_subdirectory(src)
