# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (ogl)

find_package(OpenGL REQUIRED)

# to suppress POLICY CMP0020 warning:
if(POLICY CMP0020)
cmake_policy(SET CMP0020 OLD)
endif()

# q5 instruction
# Find the Qt5Core library
# example of CMAKE_MODULE_PATH
# set(CMAKE_MODULE_PATH "D:\\Programs\\Qt5.7.0\\5.7\\msvc2015_64\\lib\\cmake\\Qt5Core\\")
# example of CMAKE_PREFIX_PATH
# set(CMAKE_PREFIX_PATH "D:\\Programs\\Qt5.7.0\\5.7\\msvc2015_64\\")
set(CMAKE_PREFIX_PATH $ENV{CMAKE_PREFIX_PATH})
# Instruct CMake to run moc automatically when needed.
#set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Widgets)

message( "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}" )
message( "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}" )
message( "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}" )
message( "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}" )
message( "_qt5Widgets_install_prefix: ${_qt5Widgets_install_prefix}" )

if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory." )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
    message( "Your Source Directory contains spaces." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
    message( "Your Build Directory contains spaces." )
endif()

# Compile external dependencies 
add_subdirectory (external)

cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP


include_directories(
    external/glfw-3.1.2/include/GLFW/
    external/glew-1.13.0/include/
    external/glm-0.9.7.1/
    ${Qt5Widgets_INCLUDE_DIRS}
    include/
    .
)

set(ALL_LIBS
    ${OPENGL_LIBRARY}
    glfw
    GLEW_1130
)

add_definitions(
    -DTW_STATIC
    -DTW_NO_LIB_PRAGMA
    -DTW_NO_DIRECT3D
    -DGLEW_STATIC
    -D_CRT_SECURE_NO_WARNINGS
    ${Qt5Widgets_DEFINITIONS}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

qt5_generate_moc(include/mainwindow.hpp moc_mainwindow.cpp)

add_executable(ogl 
    src/core.cpp
    src/app.cpp
    src/input.cpp
    src/geometry/body.cpp
    src/geometry/grid.cpp
    src/geometry/sphere.cpp
    src/geometry/cube.cpp
    src/geometry/line.cpp
    src/tutorial1.cpp
    src/tutorial2.cpp
    src/tutorial3.cpp
    src/tutorial4.cpp
    src/mainwindow.cpp
    moc_mainwindow.cpp
    src/SimpleTransform.vertexshader
    src/SingleColor.fragmentshader
    src/SimpleTransform.vertexshader
    src/SingleColor.fragmentshader
    src/TextVertexShader.fragmentshader
    src/TextVertexShader.vertexshader
    src/main.cpp
)

target_link_libraries(ogl
    ${ALL_LIBS}
    Qt5::Widgets
)

set_target_properties(ogl PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/")
create_target_launcher(ogl WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/")

SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )

add_custom_command(TARGET ogl POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different # which executes "cmake - E copy_if_different..."
        "${_qt5Widgets_install_prefix}/bin/Qt5Widgetsd.dll"
        $<TARGET_FILE_DIR:ogl>)

add_custom_command(TARGET ogl POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different # which executes "cmake - E copy_if_different..."
        "${_qt5Widgets_install_prefix}/bin/Qt5Cored.dll"
        $<TARGET_FILE_DIR:ogl>)

add_custom_command(TARGET ogl POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different # which executes "cmake - E copy_if_different..."
        "${_qt5Widgets_install_prefix}/bin/Qt5Guid.dll"
        $<TARGET_FILE_DIR:ogl>)
