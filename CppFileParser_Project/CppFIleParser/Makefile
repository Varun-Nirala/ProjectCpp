CXX = g++
CXXFLAGS = -std=c++11 -g
INCLUDES = -I./include

BUILD = ../build
SRC = ./src

SOURCES = $(wildcard $(SRC)/*.cpp)

CPP_FILES = $(notdir $(SOURCES))
OBJS = $(patsubst %.cpp, $(BUILD)/%.o, $(CPP_FILES))

TARGET = $(BUILD)/main.exe

.PHONY: all clean

all:	$(TARGET)

$(TARGET): clean $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

$(OBJS):
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(patsubst %.o, %.cpp, $(SRC)/$(notdir $@)) -o $@

clean:
	$(RM) $(BUILD)/*.*