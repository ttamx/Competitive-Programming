#!/bin/bash

TASK=meetings

java -Xmx1024M -Xss1024M -cp ${TASK}.jar grader
