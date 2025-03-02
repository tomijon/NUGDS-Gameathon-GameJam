cmake_minimum_required(VERSION 3.31)
project(AntKingdom)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB HEADERS "${CMAKE_SOURCE_DIR}/src/*.hpp")
file(GLOB SHADER_FILES "${CMAKE_SOURCE_DIR}/src/shaders/*.glsl")
source_group("shaders" FILES ${SHADER_FILES})

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${SHADER_FILES})

# Copy shaders folder to output dir.
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${CMAKE_SOURCE_DIR}/src/shaders/ "$<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders"
)

# Make sure VS runs from actual executable location
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
)

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