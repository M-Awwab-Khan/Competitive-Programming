#!/bin/bash
# Compilation flags:
# -std=c++23     : Use C++23
# -O2            : Optimization level 2 (common in CP)
# -Wall -Wextra  : Enable warnings
# -Wshadow       : Warn if a variable hides another
# -Wconversion   : Warn on type conversions
# -DLOCAL        : Useful for local debugging macros
# -fsanitize=address,undefined : Runtime error detection (optional, disable if TLE)
# -D_GLIBCXX_DEBUG: Enable STL debug checks (disable if too slow)

SOURCE="$1"
OUTPUT="a.out"

if [ -z "$SOURCE" ]; then
    echo "Usage: ./run.sh file.cpp"
    exit 1
fi

g++ -std=c++23 -O2 \
    -o "$OUTPUT" "$SOURCE"

if [ $? -eq 0 ]; then
    echo -e "\n--- Running $OUTPUT ---\n"
    ./"$OUTPUT"
else
    echo -e "\nCompilation failed."
fi
