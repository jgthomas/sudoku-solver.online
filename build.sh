#!/bin/bash
emcc solver.c -s WASM=1 -o index.js
