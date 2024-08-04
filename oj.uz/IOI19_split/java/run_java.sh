#!/bin/bash

problem=split
memory=1000

java -XX:+UseSerialGC -Xbatch -XX:-TieredCompilation -XX:CICompilerCount=1 -Xmx${memory}M -Xss${memory}M -cp $problem.jar grader
