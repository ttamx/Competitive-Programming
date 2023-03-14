#!/bin/bash

NAME=tournament

/usr/bin/g++ -DEVAL -Wall -static -O2 -o $NAME grader.cpp $NAME.cpp
