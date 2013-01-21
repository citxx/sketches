project (Rain)
cmake_minimum_required (VERSION 2.6)
add_definitions(-Wall -O2)

find_package(SDL REQUIRED)
if (NOT SDL_FOUND)
    message(FATAL_ERROR "SDL not found!")
endif (NOT SDL_FOUND)

find_package(OpenGL REQUIRED)
if (NOT OPENGL_FOUND)
    message(FATAL_ERROR "OpenGL not found!")
elseif(NOT OPENGL_GLU_FOUND)
    message(FATAL_ERROR "GLU not found!")
endif (NOT OPENGL_FOUND)

include_directories(${SDL_INCLUDE_DIR})

set (SOURCES Vector.cpp ParticleSystem.cpp RainSystem.cpp main.cpp)
add_executable(rain ${SOURCES})
target_link_libraries(rain
    ${SDL_LIBRARY}
    ${OPENGL_LIBRARIES}
)
