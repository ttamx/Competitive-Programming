#!/bin/bash

TASK=werewolf

java -Xmx1024M -Xss1024M -cp ${TASK}.jar grader
