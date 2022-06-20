#!/bin/bash
#PBS -l nodes=1:ppn=24,walltime=00:50:00
#PBS -N Mishyn_Lab4
cd $PBS_O_WORKDIR
ml icc
ml openmpi

for i in {1..24}
do
      mpirun -np $i ./m
done
