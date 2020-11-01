cmake_minimum_required(VERSION 3.0.0)
project(opengl_program VERSION 0.1.0)
    
if (WIN32)
set (VCPKG_INSTALLED_DIR "C:/vcpkg/installed")
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(OPENGL_LIBRARY_DIR "${VCPKG_INSTALLED_DIR}/x64-windows/lib")
set(GLUT_INCLUDE_DIR "${VCPKG_INSTALLED_DIR}/x64-windows/include")

find_package(GLUT REQUIRED)

add_executable(opengl_program src/main.cpp)
set_property(TARGET opengl_program PROPERTY CXX_STANDARD 14)
target_link_libraries(opengl_program PRIVATE GLUT::GLUT GLU32 OPENGL32)
add_custom_command(TARGET opengl_program POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${VCPKG_INSTALLED_DIR}/x64-windows/bin/freeglut.dll" $<TARGET_FILE_DIR:opengl_program>)    

else()
find_package(GLUT REQUIRED)

add_executable(opengl_program src/main.cpp)
set_property(TARGET opengl_program PROPERTY CXX_STANDARD 14)
target_link_libraries(opengl_program PRIVATE GLUT::GLUT GLU GL)


endif()


