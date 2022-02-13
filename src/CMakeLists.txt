if (WORDLE_ALL_WARNINGS)
    if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
    else()
        # todo : windows
    endif()
endif()

#
## Main

set(TARGET wordle)

add_executable(${TARGET}
    main.cpp
    )

target_include_directories(${TARGET} PUBLIC
    .
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET}-extra/
    )

target_link_libraries(${TARGET} PRIVATE
    imgui-sdl2
    ${CMAKE_DL_LIBS}
    )

make_directory(${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET}-extra/)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/build_timestamp-tmpl.h   ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET}-extra/build_timestamp.h @ONLY)

if (EMSCRIPTEN)
    unset(EXTRA_FLAGS)
    if (WORDLE_WASM_SINGLE_FILE)
        set(EXTRA_FLAGS "-s SINGLE_FILE=1")
        message(STATUS "Embedding WASM inside .js")
    endif()

    set_target_properties(${TARGET} PROPERTIES OUTPUT_NAME "${TARGET}-${GIT_SHA1}")

    set_target_properties(${TARGET} PROPERTIES LINK_FLAGS " \
        --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/../words@/ \
        --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/../fonts@/ \
        ${EXTRA_FLAGS} \
        ")

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/index-tmpl.html          ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET}-extra/index.html @ONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/style.css                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET}-extra/style.css COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/helpers.js               ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET}-extra/helpers.js COPYONLY)
endif()
