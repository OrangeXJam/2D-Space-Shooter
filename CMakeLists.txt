cmake_minimum_required(VERSION 3.10)
project(OpenGLProject)

# Tell the code where to find the "include" files
include_directories(external/glfw/include)
include_directories(external/glad/include)
include_directories(external)

# Find your source files
add_executable(MyApp main.cpp external/glad/src/glad.c)
set_target_properties(MyApp PROPERTIES LINK_FLAGS "-mconsole")

# Link the libraries
target_link_libraries(MyApp ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/lib-mingw-w64/libglfw3.a opengl32 gdi32)