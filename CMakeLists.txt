cmake_minimum_required(VERSION 3.28.3)
project(LinuxCS2 VERSION 1.2.3 LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2 -pthread")
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/src/imgui)


find_package(OpenGL REQUIRED)
option(BUILD_TESTING "Build tests" OFF)
find_package(glfw3 REQUIRED)
find_package(Threads REQUIRED)


add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wcast-align -Wconversion
-Wsign-conversion -Wunused -Wnull-dereference -Wdouble-promotion -Wformat=2)

add_executable(${PROJECT_NAME} src/main.cpp
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
OpenGL::GL
glfw
${CMAKE_DL_LIBS}
Threads::Threads)