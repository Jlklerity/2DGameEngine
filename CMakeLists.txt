cmake_minimum_required(VERSION 3.10)
project(GameEngine2D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ensure we're building in Debug mode
set(CMAKE_BUILD_TYPE Debug)


# Include directories for headers
include_directories(include)

# Find GLFW
find_package(glfw3 REQUIRED)

# Add executable
add_executable(GameEngine2D src/main.cpp src/glad.c src/Shader.cpp)

# Link OpenGL and GLFW
target_link_libraries(GameEngine2D PRIVATE glfw "-framework OpenGL")
