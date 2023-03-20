#!/bin/bash -eu

git clone https://github.com/ARDev1161/AmurClient.git
cd AmurClient
mkdir bin && cd bin

cmake -DCMAKE_PREFIX_PATH=$HOME/.local \
      -DCMAKE_BUILD_TYPE=Release -DGRPC_FETCHCONTENT=ON ../

cmake --build . -- -j4
