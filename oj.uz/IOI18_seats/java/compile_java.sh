#!/bin/bash

TASK=seats

javac ${TASK}.java grader.java
jar cf ${TASK}.jar *.class
