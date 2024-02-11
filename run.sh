#!/bin/bash


docker run --rm -it \
  -v $(pwd)/workdir:/workdir \
  --workdir /workdir \
  $(whoami)_c_ws \
  /bin/ash
