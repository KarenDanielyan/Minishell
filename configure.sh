#!/bin/bash

cd lib
path="`pwd`/$1"
mkdir -p $path
cd readline-8.1 && ./configure --prefix=$path
make
make install