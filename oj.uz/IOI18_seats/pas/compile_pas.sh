#!/bin/bash

TASK=seats

fpc -XS -O2 -o${TASK} grader.pas
