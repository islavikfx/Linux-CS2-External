cmake_minimum_required(VERSION 3.27)
project(LinuxCS2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -pthread")
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/src/imgui)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/gui/Menu.cpp
    src/memory/ProcessManager.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends)

target_sources(${PROJECT_NAME} PRIVATE
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp)

target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARIES}
    glfw
    dl
    ${CMAKE_THREAD_LIBS_INIT})
