#!/bin/bash

TASK=highway

java -Xmx1024M -Xss1024M -cp ${TASK}.jar grader
