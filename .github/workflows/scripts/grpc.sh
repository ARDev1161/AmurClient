#!/bin/bash

export MY_INSTALL_DIR=$HOME/.local
mkdir -p $MY_INSTALL_DIR
export PATH="$MY_INSTALL_DIR/bin:$PATH"

# sudo apt-get remove -y protobuf-compiler
sudo apt install -y build-essential autoconf automake libtool pkg-config curl make g++ unzip

# echo "Installing gRPC"
git clone --recurse-submodules -b v1.52.0 --depth 1 --shallow-submodules https://github.com/grpc/grpc

cd grpc
mkdir -p cmake/build
pushd cmake/build
cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF \
      -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \
      ../..
make -j4
make install
popd
