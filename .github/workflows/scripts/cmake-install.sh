#!/bin/bash -eu

CMAKE_VER=3.20.1

wget https://github.com/Kitware/CMake/releases/download/v${CMAKE_VER}/cmake-${CMAKE_VER}.tar.gz
tar xf cmake-${CMAKE_VER}.tar.gz
cd cmake-${CMAKE_VER}

./bootstrap
make
sudo make install

cd ../
