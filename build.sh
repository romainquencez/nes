#!/bin/bash
set -e

# Compile C source files
cc65 -O -t nes src/main.c -o obj/main.s
cc65 -O -t nes src/neslib.c -o obj/neslib.s

# Assemble all files
ca65 src/header.s -o obj/header.o
ca65 src/vectors.s -o obj/vectors.o
ca65 obj/main.s -o obj/main.o
ca65 obj/neslib.s -o obj/neslib.o

# Link into .nes ROM
ld65 -C nes.cfg obj/header.o obj/vectors.o obj/main.o obj/neslib.o \
     -o bin/game.nes

echo "Build complete: bin/game.nes"
