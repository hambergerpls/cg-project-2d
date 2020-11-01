cmake_minimum_required(VERSION 3.0.0)
project(opengl_program VERSION 0.1.0)


if(WIN32)
    
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
find_package(OpenGL REQUIRED)

endif(WIN32)

find_package(GLUT REQUIRED)
add_executable(opengl_program src/main.cpp)
set_property(TARGET opengl_program PROPERTY CXX_STANDARD 14)

target_link_libraries(opengl_program PRIVATE GLUT::GLUT GL GLU)