#!/bin/bash

TASK=catdog

javac ${TASK}.java grader.java
jar cf ${TASK}.jar *.class
