#!/bin/bash

NAME=game

/usr/bin/gcc -DEVAL -static -O2 -o $NAME grader.c $NAME.c -lm
