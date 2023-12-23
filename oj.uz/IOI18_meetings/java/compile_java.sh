#!/bin/bash

TASK=meetings

javac ${TASK}.java grader.java
jar cf ${TASK}.jar *.class
