#!/usr/bin/env bash

clang -g repro.c $(pkg-config --cflags --libs hidapi) -pthread -o repro