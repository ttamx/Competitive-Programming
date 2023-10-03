#!/bin/bash

TASK=werewolf

fpc -XS -O2 -o${TASK} grader.pas
