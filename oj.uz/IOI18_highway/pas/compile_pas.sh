#!/bin/bash

TASK=highway

fpc -XS -O2 -o${TASK} grader.pas
