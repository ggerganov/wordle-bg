set(TARGET wordle)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/build_timestamp-tmpl.h ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/build_timestamp.h @ONLY)

add_executable(${TARGET}
    main.cpp
    common.cpp
    )

target_include_directories(${TARGET} PRIVATE
    ..
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/
    )

target_link_libraries(${TARGET} PRIVATE
    imgui-sdl2
    ${CMAKE_DL_LIBS}
    )

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/index-tmpl.html  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/index.html @ONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/style.css        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/style.css COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/gghelpers.js     ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/gghelpers.js COPYONLY)
