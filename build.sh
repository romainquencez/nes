#!/usr/bin/env bash
set -e

CC65_HOME=/usr/local/share/cc65   # ajuste si besoin

mkdir -p build

# 1) C -> ASM
cc65 -O -t nes src/main.c -o build/main.s

# 2) ASM -> OBJ
ca65 -t nes build/main.s -o build/main.o

# 3) LINK -> ROM .nes
ld65 -C cfg/nes.cfg -o main.nes build/main.o
