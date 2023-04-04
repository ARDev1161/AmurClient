#!/bin/bash -eu

apt-get install -y cmake \
      libssl-dev \
      libconfig++-dev libconfig-dev \
  && apt-get clean
