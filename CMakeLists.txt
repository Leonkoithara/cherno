cmake_minimum_required(VERSION 3.16.3)

project(LearnOpenGL)

set(CMAKE_BUILD_TYPE Debug)

# glfw
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARY_DIRS})

# opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})


file(GLOB SOURCES src/*.cpp src/scenes/*.cpp)
file(GLOB LIB_SOURCES src/vendor/*/*.cpp)

include_directories(src/vendor)

add_executable(out ${SOURCES})

target_sources(
  out
    PRIVATE
      ${LIB_SOURCES}
)

target_link_libraries(
  out
  glfw
  dl
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
)
