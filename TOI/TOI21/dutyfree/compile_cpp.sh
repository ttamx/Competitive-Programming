#!/bin/bash

problem="duty_free"
grader_name="grader"

g++ -std=gnu++17 -O -Wall -pipe -static -o "${problem}" "${grader_name}.cpp" "${problem}.cpp"

