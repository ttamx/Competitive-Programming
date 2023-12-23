#!/bin/bash

problem=paint

gcc -O2 -std=c11 -static -o $problem grader.c $problem.c
