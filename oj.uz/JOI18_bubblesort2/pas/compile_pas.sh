#!/bin/bash

TASK=bubblesort2

fpc -XS -O2 -o${TASK} grader.pas
