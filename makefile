CXX = g++
MINGW =  x86_64-w64-mingw32
CXXFLAGS = -Wall -Wextra -O2 -std=c++17 -I ./src/header/
LDFLAGS = -lfreeimage 
LWINDOWS = -IL./src/lib/
SRC = src/quadtree/quadtree.cpp src/main.cpp src/methods/maxpixeldifference.cpp src/methods/entropy.cpp src/methods/meanabsolutedeviaton.cpp src/methods/variance.cpp src/utils/iohandler/iohandler.cpp src/utils/imageloader/imageloader.cpp src/utils/ascii/ascii.cpp src/compression/compression.cpp
BIN = ./bin

WINDOWS = YuukaPress
LINUX = YuukaPress

windows:
	mkdir -p $(BIN) 
	$(MINGW)-$(CXX) $(CXXFLAGS) -o $(BIN)/$(WINDOWS).exe $(SRC) $(LWINDOWS) $(LDFLAGS)

linux: 
	mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) -o $(BIN)/$(LINUX) $(SRC) $(LDFLAGS)

build: windows linux

clean:
	rm -rf $(BIN)/*.exe
	rm -rf $(BIN)/$(LINUX)

all: build