#!/usr/bin/env bash

HELP=$(cat <<-END
Usage: ./setup-reactphysics3d.sh [RP3D_VERSION_TAG]

Setup ReactPhysics3d in the system given the tag version.

RP3D_VERSION_TAG: default value is v0.8.0
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

  # Set ogre version
  RP3D_VERSION_TAG="${RP3D_VERSION_TAG:-v0.8.0}";
  echo "ReactPhysics3d version: $RP3D_VERSION_TAG"

  # Install dependencies if is needed
  DEPENDENCIES=(libgles2-mesa-dev libsdl2-dev libxt-dev libxaw7-dev doxygen zziplib-bin cmake-qt-gui cmake)
  for i in "${DEPENDENCIES[@]}"; do
    if [ "$(is_package_installed $i)" = "no" ]; then
      echo $i
      sudo apt install -y $i
    fi
  done

  git clone https://github.com/DanielChappuis/reactphysics3d.git
  cd reactphysics3d

  git checkout $RP3D_VERSION_TAG

  # Build reactphysics3d
  cmake .
  cmake --build . --config Release

  # Install reactphysics3d
  sudo cmake --build . --config Release --target install

  # Remove reactphysics3d repo
  cd ..
  rm -rf reactphysics3d

fi
