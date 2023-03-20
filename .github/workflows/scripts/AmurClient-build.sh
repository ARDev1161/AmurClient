#!/bin/bash -eu

git clone https://github.com/ARDev1161/AmurClient.git
cd AmurClient
mkdir bin && cd bin

gRPC_dir=/opt/hostedtoolcache/grpc/1.48.2/x64

cmake -DCMAKE_INSTALL_RPATH=${gRPC_dir}/lib \
      -DCMAKE_PREFIX_PATH=${gRPC_dir} \
      -DCMAKE_BUILD_TYPE=Release -DGRPC_FETCHCONTENT=OFF ../

cmake --build . -- -j4
