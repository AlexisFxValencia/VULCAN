#!/bin/bash

display_help() {
  echo "Usage: $0 [-d] [-h]"
  echo "Options:"
  echo "  -d    Compile in Debug mode (default: Release)"
  echo "  -h    Display this help"
  echo "  -c    only compilation (doesn't run the program in the end)"
  exit 0
}

compile_only="false"
# Par défaut, le mode de compilation est Release
build_mode="Release"

# Vérifier si l'argument -d est passé
while getopts ":dhc" opt; do
  case $opt in
    d)
      build_mode="Debug"
      ;;
    h)
      display_help
      ;;
    c)
      compile_only="true"
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      exit 1
      ;;
  esac
done

file_path=$(readlink -f "$0")
ROOT_DIR=$(dirname "$file_path")
echo $ROOT_DIR
export SFML_DIR="$ROOT_DIR/lib/SFML-2.5.1-linux-gcc-64-bit/SFML-2.5.1/"

# Créer le répertoire de build en fonction du mode choisi
mkdir -p "$build_mode"
cd "$build_mode"

# Lancer CMake avec le mode choisi
cmake -DCMAKE_BUILD_TYPE=$build_mode ..

# Compiler et lancer le programme
make
cp -r ../common/input_files .
cp -r ../common/themes .
if [ "$compile_only" = "false" ]; then
 ./VULCAN
fi


