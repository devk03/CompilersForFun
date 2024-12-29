#!/bin/bash
# Example: If you run "./launch.sh hello.c", this script will:

# 1. Compile: gcc hello.c -o hello
gcc $1 -o $(basename $1 .c) && \
# 2. Run: ./hello
./$(basename $1 .c)
# 3. Clean up: rm hello
rm $(basename $1 .c)

# Usage example:
# $ ./launch.sh hello.c
# This will compile hello.c, run it, and clean up the executable