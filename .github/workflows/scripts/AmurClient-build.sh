#!/bin/bash -eu

git clone https://github.com/ARDev1161/AmurClient.git
cd AmurClient
mkdir bin && cd bin

cmake -DCMAKE_LIBRARY_PATH=/opt/hostedtoolcache/grpc/1.48.2/x64/lib -DCMAKE_PREFIX_PATH=/opt/hostedtoolcache/grpc/1.48.2/x64 -DCMAKE_BUILD_TYPE=Release -DGRPC_FETCHCONTENT=OFF ../

cmake --build . -- -j4
