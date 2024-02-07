#!/bin/bash

file_path=$(readlink -f "$0")
ROOT_DIR=$(dirname "$file_path")
echo $ROOT_DIR
export SFML_DIR="$ROOT_DIR/lib/SFML-2.5.1-linux-gcc-64-bit/SFML-2.5.1/"
echo $SFML_DIR
cd $ROOT_DIR/lib/TGUI-0.9.5
cmake -S . -B build -D TGUI_BACKEND=SFML
cd build
make -j8
cd $ROOT_DIR
pwd
