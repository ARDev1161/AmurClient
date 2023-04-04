#!/bin/bash -eu

apt-get install -y cmake \
      libssl-dev \
      libconfig++-dev libconfig-dev \
      libprotobuf23 \
      protobuf-compiler \
  && apt-get clean
