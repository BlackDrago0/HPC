#!/bin/bash
cd $PBS_O_WORKDIR
stat=$(qsub -v arg1="100" -W depend=on:100 stat.sh)

for i in {1..100}
do
        qsub -v arg1="$i" -W depend=beforeany:$stat task.sh
done
