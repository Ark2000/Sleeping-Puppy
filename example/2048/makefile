CC = g++

EXE = 2048

SRC = Main.cpp
SRC += ../../obj/*.o

INCLUDE_PATH = -I../../dep/SDL2-2.0.10/x86_64-w64-mingw32/include/SDL2
INCLUDE_PATH += -I../../dep/SDL2_image-2.0.5/x86_64-w64-mingw32/include/SDL2
INCLUDE_PATH += -I../../dep/SDL2_mixer-2.0.4/x86_64-w64-mingw32/include/SDL2
LIBRARY_PATH = -L../../dep/SDL2-2.0.10/x86_64-w64-mingw32/lib
LIBRARY_PATH += -L../../dep/SDL2_image-2.0.5/x86_64-w64-mingw32/lib
LIBRARY_PATH += -L../../dep/SDL2_mixer-2.0.4/x86_64-w64-mingw32/lib
LIBRARY_PATH += -L../../lib
COMPILER_FLAG = -Wall -Wl,-subsystem,windows -std=c++11
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2_image -lSDL2_mixer -lSDL2

all: 2048

2048:
	$(CC) $(SRC) $(INCLUDE_PATH) $(LIBRARY_PATH) $(LINKER_FLAGS) $(COMPILER_FLAG) -o 2048
