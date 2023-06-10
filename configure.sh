#!/bin/bash

echo "Enter the directory where configured readline will be stored"

read rl_path

mkdir -p $rl_path
./configure --prefix=$(find $HOME -name $rl_path -type d 2>/dev/null) && \
make clean all install