cmake_minimum_required(VERSION 3.10)
project(GameEngine2D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set build type
set(CMAKE_BUILD_TYPE Debug)

#Configure using GCC 14.2.0 x86_64-w64-mingw32 kit

# Include directories (you can remove this if you're adding GLFW via subdirectory)
#include_directories(${CMAKE_SOURCE_DIR}/include)

# Add GLFW as a subdirectory (make sure to adjust if the GLFW source is located elsewhere)
add_subdirectory(include/glfw)

# Add GLAD directly (don't use find_package for GLAD)
# Create a glad library from the source file
add_library(glad src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Add executable (without glad.c since it's now in its own library)
add_executable(GameEngine2D src/main.cpp src/Shader.cpp)

# Link libraries
target_link_libraries(GameEngine2D PRIVATE glfw glad)

# Optionally, copy necessary DLLs after building if needed (uncomment if required)
# add_custom_command(TARGET GameEngine2D POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#    "${GLFW_DLL_PATH}/glfw3.dll"
#    $<TARGET_FILE_DIR:GameEngine2D>)
