#!/bin/bash -eu

git clone https://github.com/ARDev1161/AmurClient.git
cd AmurClient
mkdir bin && cd bin

cmake -DCMAKE_BUILD_TYPE=Release -DGRPC_FETCHCONTENT=OFF ../

cmake --build . -- -j4
