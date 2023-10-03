#!/bin/bash

TASK=werewolf

javac ${TASK}.java grader.java
jar cf ${TASK}.jar *.class
