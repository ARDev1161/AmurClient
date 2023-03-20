#!/bin/bash -eu

git clone https://github.com/ARDev1161/AmurClient.git
cd AmurClient
mkdir bin && cd bin

# If gRPC is globally installed
cmake -DCMAKE_PREFIX_PATH=${GRPC_ROOT}/lib/cmake/grpc -DCMAKE_BUILD_TYPE=Release -DGRPC_FETCHCONTENT=OFF ../

cmake --build . -- -j4
