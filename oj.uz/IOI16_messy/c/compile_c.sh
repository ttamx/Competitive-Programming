#!/bin/bash

problem=messy

gcc -O2 -std=c11 -static -o $problem grader.c $problem.c
