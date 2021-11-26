#!/usr/bin/env bash

HELP=$(cat <<-END
Usage: ./setup-bulletphysic.sh [BULLET_VERSION_TAG]

Setup BulletPhysics in the system given the tag version.

BULLET_VERSION_TAG: default value is v0.8.0
.
END
)

is_package_installed() {
  PACKAGE=$1;
  IS_INSTALL=$(dpkg-query -W --showformat='${Status}\n' $PACKAGE | grep "install ok installed")
  echo $(if [ "$IS_INSTALL" = "install ok installed" ]; then echo "yes"; else echo "no"; fi)
}

if [ "$1" = "-h" ] || [ "$1" = "help" ]; then
  echo "$HELP"
else

  # Set bullet3 version
  BULLET_VERSION_TAG="${BULLET_VERSION_TAG:-3.17}";
  echo "bulletphysics version: $BULLET_VERSION_TAG"

  # Install dependencies if is needed
  DEPENDENCIES=(libgles2-mesa-dev libsdl2-dev libxt-dev libxaw7-dev zziplib-bin cmake-qt-gui cmake build-essential python-dev python3-dev)
  for i in "${DEPENDENCIES[@]}"; do
    if [ "$(is_package_installed $i)" = "no" ]; then
      echo $i
      sudo apt install -y $i
    fi
  done

  git clone https://github.com/bulletphysics/bullet3.git
  cd bullet3

  git checkout $BULLET_VERSION_TAG

  mkdir -p build_cmake
  cd build_cmake
  #  cmake -DBUILD_PYBULLET=ON -DBUILD_PYBULLET_NUMPY=ON -DUSE_DOUBLE_PRECISION=ON -DBT_USE_EGL=ON -DCMAKE_BUILD_TYPE=Release ..
  cmake -DBUILD_PYBULLET=ON -DBUILD_PYBULLET_NUMPY=ON -DUSE_DOUBLE_PRECISION=ON -DBT_USE_EGL=ON -DCMAKE_BUILD_TYPE=Debug ..
  #  cmake --build . --config Release

  # Install bullet3
  sudo cmake --build . --config Debug --target install

  # Build bullet3
  cd build3
  ./premake4_linux64 --double gmake
  cd gmake
  make

  # Remove bullet3 repo
#  cd ../..
#  sudo rm -rf bullet3

fi
