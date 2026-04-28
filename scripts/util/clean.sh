#!/usr/bin/env bash

VM_INDEX=NULL source env.bash

cd $BAO_DEMOS_BAO
make clean
cd "$VM"0
make clean
cd "$VM"1
make clean
cd "$VM"2
make clean
cd "$VM"3
make clean

rm $BAO_DEMOS_WRKDIR_IMGS/*.bin
