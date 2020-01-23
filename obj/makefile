CC = g++

SRC = ../src/*.cpp

INCLUDE_PATH = -I../dep/SDL2-2.0.10/x86_64-w64-mingw32/include/SDL2
LIBRARY_PATH = -L../dep/SDL2-2.0.10/x86_64-w64-mingw32/lib
COMPILER_FLAG = -Wall -O2
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2


all: binary

binary:
	$(CC) $(SRC) $(INCLUDE_PATH) $(LIBRARY_PATH) $(LINKER_FLAGS) $(COMPILER_FLAG) -c