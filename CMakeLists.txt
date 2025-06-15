cmake_minimum_required(VERSION 3.31)
project(OpenGL)

set(CMAKE_CXX_STANDARD 20)

# Set paths to GLEW and GLFW
set(LIBS_ROOT "Z:/jetbrains/CLion 2025.1.2/bin/mingw")

set(GLFW_INCLUDE_DIR "${LIBS_ROOT}/include")
set(GLFW_LIBRARY "${LIBS_ROOT}/lib/libglfw3.a")

set(GLEW_INCLUDE_DIR "${LIBS_ROOT}/include")
set(GLEW_LIBRARY "${LIBS_ROOT}/lib/libglew32.a")

add_executable(OpenGL
        src/Main.cpp
        src/Window/Window.cpp
        src/Window/Window.h
        src/Shader/Shader.cpp
        src/Shader/Shader.h
)

# Add include directories for GLEW and GLFW
target_include_directories(OpenGL PRIVATE ${GLFW_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})

# Link libraries
target_link_libraries(OpenGL
        PRIVATE
        ${GLFW_LIBRARY}   # libglfw3.a
        ${GLEW_LIBRARY}   # libglew32s.a
        opengl32          # OpenGL
)
