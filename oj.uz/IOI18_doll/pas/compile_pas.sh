#!/bin/bash

TASK=doll

fpc -XS -O2 -o${TASK} grader.pas
