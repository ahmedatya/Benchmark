CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
CC = g++
DEBUG = -g
CFLAGS = -Wall -c  $(DEBUG)
LFLAGS = -Wall $(DEBUG)
EXEC = Bench

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
 CFLAGS += -std=c++0x
 LFLAGS += -pthread
endif

$(EXEC): $(OBJ_FILES)
	$(CC) $(LFLAGS) $(OBJ_FILES) -o $(EXEC)

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm obj/*.o $(EXEC)
