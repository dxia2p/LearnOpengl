cmake_minimum_required(VERSION 3.18)

project(LearnOpenGL)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES main.cpp glad.c shader.cpp camera.cpp mesh.cpp model.cpp debug.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

target_compile_definitions(LearnOpenGL PRIVATE ASSETS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/")

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ../dependencies/includes)
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE ../dependencies/lib)
target_link_libraries(${CMAKE_PROJECT_NAME} glfw3 GL assimp)
