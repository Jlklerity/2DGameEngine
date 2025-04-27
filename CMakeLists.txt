cmake_minimum_required(VERSION 3.10)
project(GameEngine2D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ensure we're building in Debug mode
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_PREFIX_PATH "/opt/homebrew")  # Helps CMake find Homebrew packages

# Include directories for headers
include_directories(include)

# Find GLFW
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
# Find freetype (render text on screen)
find_package(Freetype REQUIRED)

message(STATUS "FREETYPE_INCLUDE_DIRS: ${FREETYPE_INCLUDE_DIRS}")

# Add executable
add_executable(GameEngine2D src/main.cpp src/glad.c src/Shader.cpp src/TextRenderer.cpp
                src/Star.cpp src/Texture.cpp src/Platform.cpp src/Wall.cpp src/Collision.cpp)

target_include_directories(GameEngine2D PRIVATE ${FREETYPE_INCLUDE_DIRS})

# Link OpenGL and GLFW
target_link_libraries(GameEngine2D PRIVATE glfw "-framework OpenGL" ${FREETYPE_LIBRARIES} glm::glm) 
