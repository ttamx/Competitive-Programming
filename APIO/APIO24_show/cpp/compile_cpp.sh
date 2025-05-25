#!/bin/bash

g++ -std=gnu++17 -O2 -Wall -pipe -static -o grader Alice.cpp Bob.cpp grader.cpp
