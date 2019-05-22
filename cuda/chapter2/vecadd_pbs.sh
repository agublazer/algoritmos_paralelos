#!/bin/sh
#PBS -N vecadd
#PBS -l nodes=1:ppn=1:gpus=1

cd $PBS_O_WORKDIR
/usr/local/cuda/bin/nvcc -std=c++11 vecadd.cu -o vecadd.out
./vecadd.out

