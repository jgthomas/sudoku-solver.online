#!/bin/bash
if [[ "$1" == "clean" ]]; then
        rm index.js index.wasm
else
        emcc solver.c -s WASM=1 -o index.js
fi
