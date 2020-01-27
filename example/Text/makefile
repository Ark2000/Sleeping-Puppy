CC = g++

EXE = text

SRC = Main.cpp ../../obj/*.o

INCLUDE_PATH = -I../../dep/SDL2-2.0.10/x86_64-w64-mingw32/include/SDL2
INCLUDE_PATH += -I../../dep/SDL2_image-2.0.5/x86_64-w64-mingw32/include/SDL2
LIBRARY_PATH = -L../../dep/SDL2-2.0.10/x86_64-w64-mingw32/lib
LIBRARY_PATH += -L../../dep/SDL2_image-2.0.5/x86_64-w64-mingw32/lib
COMPILER_FLAG = -Wall -Wl,-subsystem,windows -std=c++11
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

all: $(EXE)

$(EXE):
	$(CC) $(SRC) $(INCLUDE_PATH) $(LIBRARY_PATH) $(LINKER_FLAGS) $(COMPILER_FLAG) -o $(EXE)