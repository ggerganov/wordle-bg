if (APPLE)
    set(ADDITIONAL_LIBRARIES "-framework Cocoa")
else (APPLE)
    unset(ADDITIONAL_LIBRARIES)
endif (APPLE)

add_library(imgui SHARED
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    )

target_include_directories(imgui INTERFACE
    .
    )

target_include_directories(imgui PRIVATE
    imgui
    )

target_link_libraries(imgui PRIVATE
    ${ADDITIONAL_LIBRARIES}
    )

if (EMSCRIPTEN)
    add_library(imgui-sdl2
        imgui-extra/imgui_impl.cpp
        imgui/backends/imgui_impl_sdl.cpp
        imgui/backends/imgui_impl_opengl3.cpp
        )

    target_include_directories(imgui-sdl2 PRIVATE
        imgui
        imgui-extra
        )

    target_link_libraries(imgui-sdl2 PUBLIC
        imgui
        )
else()
    find_package(OpenGL REQUIRED)

    add_library(imgui-sdl2 SHARED
        imgui-extra/imgui_impl.cpp
        imgui/backends/imgui_impl_sdl.cpp
        imgui/backends/imgui_impl_opengl3.cpp
        )

    target_include_directories(imgui-sdl2 PUBLIC
        ${SDL2_INCLUDE_DIRS}
        )

    target_include_directories(imgui-sdl2 PRIVATE
        imgui
        imgui-extra
        )

    target_link_libraries(imgui-sdl2 PUBLIC
        imgui
        ${SDL2_LIBRARIES}
        ${OPENGL_LIBRARIES} # TODO : make this private?
        )

    target_link_libraries(imgui-sdl2 PRIVATE
        ${CMAKE_DL_LIBS}
        ${CMAKE_THREAD_LIBS_INIT}
        ${ADDITIONAL_LIBRARIES}
        )
endif()
