#!/bin/bash -eu

GRPC_VER=1.35.0

cmake --version

sudo apt install -y build-essential autoconf libtool pkg-config

git clone --recurse-submodules -b v${GRPC_VER} https://github.com/grpc/grpc
cd grpc

echo "Building grpc...\n"
mkdir -p cmake/build
pushd cmake/build

cmake -DgRPC_INSTALL=ON \
      -DgRPC_BUILD_TESTS=OFF \
      -DgRPC_BUILD_CSHARP_EXT=OFF \
      ../..
make
sudo make install
popd

echo "Building abseil...\n"
mkdir -p third_party/abseil-cpp/cmake/build
pushd third_party/abseil-cpp/cmake/build
cmake -DCMAKE_POSITION_INDEPENDENT_CODE=TRUE \
      ../..
make -j
sudo make install
popd

echo "Building examples...\n"
cd examples/cpp/helloworld
mkdir -p cmake/build
pushd cmake/build
cmake ../..
make -j
