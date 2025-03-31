#!/bin/bash

CXXFLAGS="-Wall -Wextra -O2 -std=c++17 -I ./src/header/"
LDFLAGS="-L/usr/local/lib -lfreeimage"

# Define paths
BIN_DIR="bin"
EXEC="$BIN_DIR/YuukaPress"

# Source files
SRC="src/quadtree/quadtree.cpp src/main.cpp src/methods/maxpixeldifference.cpp src/methods/entropy.cpp src/methods/meanabsolutedeviaton.cpp src/methods/variance.cpp src/utils/iohandler/iohandler.cpp src/utils/imageloader/imageloader.cpp src/utils/ascii/ascii.cpp"

# Object files
OBJ=""
for file in $SRC; do
    filename=$(basename "$file" .cpp)
    OBJ="$OBJ $BIN_DIR/$filename.o"
done

# Generate Makefile
cat <<EOF > makefile
# Auto-generated Makefile

CXX = g++
CXXFLAGS = $CXXFLAGS
LDFLAGS = $LDFLAGS
BIN_DIR = $BIN_DIR

SRC = $SRC
OBJ = $OBJ
EXEC = $EXEC

all: \$(BIN_DIR) \$(EXEC)

\$(BIN_DIR):
	mkdir -p \$(BIN_DIR)

\$(EXEC): \$(OBJ)
	\$(CXX) \$(CXXFLAGS) \$(OBJ) -o \$(EXEC) \$(LDFLAGS)

bin/%.o: src/**/*.cpp
	\$(CXX) \$(CXXFLAGS) -c \$(filter %/\$(notdir \$*).cpp, \$(SRC)) -o \$@

clean:
	find \$(BIN_DIR) -type f ! -name '.gitkeep' -delete

run: \$(EXEC)
	./\$(EXEC)
EOF

echo "Makefile generated successfully!"
