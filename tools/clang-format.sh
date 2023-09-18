#!/bin/bash

find ../src -path "../src/extern" -prune -o \( -name "*.cpp" -o -name "*.c" -o -name "*.h" -o -name "*.ino" \) | xargs -I {} clang-format -style=file -i {}
