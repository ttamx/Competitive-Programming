#!/bin/bash

TASK=combo

g++ -std=gnu++14 -Wall -O2 -static -o ${TASK} grader.cpp ${TASK}.cpp
