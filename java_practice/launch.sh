#!/bin/bash
# This script combines these commands:
#   javac HelloWorld.java     # compiles the java file
#   java HelloWorld          # runs the compiled program
#   rm HelloWorld.class      # removes the compiled class file

javac $1 && java $(basename $1 .java)
rm $(basename $1 .java).class