cmake_minimum_required(VERSION 3.18)
project(bugsinvation)

find_package(OGRE REQUIRED COMPONENTS Bites RTShaderSystem CONFIG)

set(CMAKE_CXX_STANDARD 11)

configure_file(resources.cfg ${CMAKE_CURRENT_BINARY_DIR}/resources.cfg @ONLY)

add_executable(bugsinvation main.cpp)

target_link_libraries(bugsinvation OgreBites OgreRTShaderSystem)
