#!/bin/bash

TASK=catdog

fpc -XS -O2 -o${TASK} grader.pas
