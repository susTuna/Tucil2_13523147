@echo off
setlocal enabledelayedexpansion

:: Set compiler flags for Windows
set "CXXFLAGS=-IC:/FreeImage/Dist"
set "LDFLAGS=-LC:/FreeImage/Dist -lFreeImage"
set "BIN_DIR=bin"
set "EXEC=%BIN_DIR%\YuukaPress.exe"

:: Define source files
set "SRC=src\quadtree\quadtree.cpp src\main.cpp src\methods\maxpixeldifference.cpp src\methods\entropy.cpp src\methods\meanabsolutedeviaton.cpp src\methods\variance.cpp src\utils\iohandler\iohandler.cpp src\utils\imageloader\imageloader.cpp src\utils\ascii\ascii.cpp"

:: Generate object file list
set "OBJ="
for %%f in (%SRC%) do (
    for %%g in (%%~nf) do (
        set "OBJ=!OBJ! %BIN_DIR%\%%g.o"
    )
)

:: Create the Makefile
(
echo # Auto-generated Makefile

echo CXX = g++
echo CXXFLAGS = %CXXFLAGS%
echo LDFLAGS = %LDFLAGS%
echo BIN_DIR = %BIN_DIR%

echo SRC = %SRC%
echo OBJ = %OBJ%
echo EXEC = %EXEC%

echo all: ^$(BIN_DIR) ^$(EXEC)

echo ^$(BIN_DIR):
echo 	mkdir ^$(BIN_DIR)

echo ^$(EXEC): ^$(OBJ)
echo 	^$(CXX) ^$(CXXFLAGS) ^$(OBJ) -o ^$(EXEC) ^$(LDFLAGS)

echo bin/%%.o: src/**/*.cpp
echo 	^$(CXX) ^$(CXXFLAGS) -c ^$(filter %/$(notdir $*).cpp, ^$(SRC)) -o ^$@

echo clean:
echo 	del /Q ^$(BIN_DIR)\*

echo run: ^$(EXEC)
echo 	^$(EXEC)
) > Makefile

echo Makefile generated successfully!