#!/bin/sh

gcc -DNORMAL -O0 -o o0 matmul.c
gcc -DNORMAL -O2 -o o2 matmul.c
gcc -DLOOP_UNROLLING -O2 -o loop_unrolling matmul.c
gcc -DBLOCKING -O2 -o blocking matmul.c
gcc -DOPENMP -fopenmp -O2 -o openmp matmul.c