# Auto-generated Makefile

CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=c++17 -I ./src/header/
LDFLAGS = -L/usr/local/lib -lfreeimage
BIN_DIR = bin

SRC = src/quadtree/quadtree.cpp src/main.cpp src/methods/maxpixeldifference.cpp src/methods/entropy.cpp src/methods/meanabsolutedeviaton.cpp src/methods/variance.cpp src/utils/iohandler/iohandler.cpp src/utils/imageloader/imageloader.cpp src/utils/ascii/ascii.cpp
OBJ = bin/quadtree.o bin/main.o bin/maxpixeldifference.o bin/entropy.o bin/meanabsolutedeviaton.o bin/variance.o bin/iohandler.o bin/imageloader.o bin/ascii.o
EXEC = bin/YuukaPress

all: $(BIN_DIR) $(EXEC)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(EXEC) $(LDFLAGS)

bin/%.o: src/**/*.cpp
	$(CXX) $(CXXFLAGS) -c $(filter %/$(notdir $*).cpp, $(SRC)) -o $@

clean:
	find $(BIN_DIR) -type f ! -name '.gitkeep' -delete

run: $(EXEC)
	./$(EXEC)
