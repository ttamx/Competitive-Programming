#!/bin/bash

TASK=highway

javac ${TASK}.java grader.java
jar cf ${TASK}.jar *.class
