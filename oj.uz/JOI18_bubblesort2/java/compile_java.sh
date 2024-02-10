#!/bin/bash

TASK=bubblesort2

javac ${TASK}.java grader.java
jar cf ${TASK}.jar *.class
