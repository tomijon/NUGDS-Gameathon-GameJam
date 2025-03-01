cmake_minimum_required(VERSION 3.31)
project(AntKingdom)

set(CMAKE_CXX_STANDARD 20)


set(SOURCES
	src/main.cpp
	src/mesh.hpp
	src/mesh.cpp
	src/unique_buffer.hpp
	src/window.hpp
	src/window.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# GLAD
include(FetchContent)
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG master
)

set(GLAD_PROFILE "core" CACHE STRING "" FORCE)
set(GLAD_API "gl=4.6" CACHE STRING "" FORCE)
set(GLAD_GENERATOR "c" CACHE STRING "" FORCE)

FetchContent_MakeAvailable(glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

# GLFW
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4  # Latest stable release as of now
)
FetchContent_MakeAvailable(glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

# Platform Specific OpenGL Lib
if(WIN32)
  target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
elseif(APPLE)
  find_library(OpenGL_LIBRARY OpenGL)
  target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenGL_LIBRARY})
else()
  target_link_libraries(${PROJECT_NAME} PRIVATE GL)
endif()