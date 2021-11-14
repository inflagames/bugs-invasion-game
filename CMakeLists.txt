cmake_minimum_required(VERSION 3.18)
project(bugsinvation)

# Needed for ReactPhysics3D in windows and mac os
if(WIN32)
    list(APPEND CMAKE_PREFIX_PATH "C:\\Program Files (x86)\\ReactPhysics3D")
elseif(APPLE)
    list(APPEND CMAKE_PREFIX_PATH "/usr/local/lib/cmake/ReactPhysics3D")
endif()

find_package(OGRE REQUIRED COMPONENTS Bites RTShaderSystem CONFIG)
find_package(ReactPhysics3D REQUIRED)

set(CMAKE_CXX_STANDARD 11)

configure_file(bin/game/resources.cfg ${CMAKE_CURRENT_BINARY_DIR}/resources.cfg @ONLY)

add_executable(bugsinvation bin/game/main.cpp bin/game/inc/Field.h bin/game/src/Field.cpp bin/game/inc/Game.h bin/game/src/Game.cpp bin/game/inc/Tanks/Tank.h bin/game/src/Tanks/Tank.cpp bin/game/inc/PhysicBase.h)

target_link_libraries(bugsinvation OgreBites OgreRTShaderSystem OgreTerrain ReactPhysics3D::ReactPhysics3D)
