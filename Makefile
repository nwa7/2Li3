CC = g++
CXXFLAGS = -g -Wall -Wextra
CPPFLAGS = -MMD
LDFLAGS = $(shell pkg-config --cflags --libs sdl2) -lGL -lGLU -lm


SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
DEP = $(SRC:.cpp=.d)
BIN = main

all : $(OBJ)
	$(CC) $^ $(LDFLAGS) -o $(BIN)


-include $(DEP)

clean :
	$(RM) $(BIN) $(OBJ) $(DEP)