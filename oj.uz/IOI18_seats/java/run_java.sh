#!/bin/bash

TASK=seats

java -Xmx1024M -Xss1024M -cp ${TASK}.jar grader
