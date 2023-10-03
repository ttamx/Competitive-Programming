#!/bin/bash

TASK=doll

javac ${TASK}.java grader.java
jar cf ${TASK}.jar *.class
