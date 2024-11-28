#!/bin/bash

TASK=catdog

java -Xmx512M -Xss64M -cp ${TASK}.jar grader
