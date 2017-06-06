CXX = g++
CXXFLAGS = -std=c++11 -g -Wall
INCLUDES = -I.\include

BUILD = ..\build
SRC = .\src

SOURCES = $(wildcard src/*.cpp)

OBJS_FILES = $(notdir $(SOURCES))
OBJS = $(patsubst %.cpp, $(BUILD)\\%.o, $(OBJS_FILES))

#$(error VAR is $(OBJS))

MAIN = main

.PHONY: all run clean

all:	$(MAIN)

$(MAIN):	$(SOURCES)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(BUILD)\$(MAIN) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $(BUILD)\$(@F)

clean:
	cd $(BUILD)
	rm -f *.o *.exe