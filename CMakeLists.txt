cmake_minimum_required(VERSION 3.18)
project(bugsinvation)

#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
        CACHE STRING "Vcpkg toolchain file")

include_directories(${BULLET_INCLUDE_DIR})

find_package(imgui REQUIRED)
find_package(SDL2 REQUIRED)
find_package(ZLIB REQUIRED)
find_package(OGRE CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)

configure_file(resources.cfg ${CMAKE_CURRENT_BINARY_DIR}/resources.cfg @ONLY)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

add_executable(bugsinvation bin/game/main.cpp bin/game/inc/Field.h bin/game/src/Field.cpp bin/game/inc/Game.h bin/game/src/Game.cpp bin/game/inc/Tanks/Tank.h bin/game/src/Tanks/Tank.cpp bin/game/inc/PhysicBase.h bin/game/inc/Utils.h bin/game/inc/Physics.h bin/game/src/Physics.cpp)

target_link_libraries(bugsinvation OgreMain OgreBites LinearMath Bullet3Common BulletDynamics BulletSoftBody)
