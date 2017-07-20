CXX = g++
CXXFLAGS = -std=c++11

INC_DIR = ./include
SRC_DIR = ./src
BUILD_DIR = ../build

INCFLAGS = $(addprefix -I,$(INC_DIR))
CPPFLAGS ?= $(INCFLAGS) -MMD -MP

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

CPP_FILES = $(notdir $(SRC_FILES))
OBJ_FILES = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(CPP_FILES))

TARGET = $(BUILD_DIR)/main.exe

.PHONY: all clean

all:	$(TARGET)

$(TARGET):	$(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ_FILES)

$(OBJ_FILES):
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(patsubst %.o, %.cpp, $(SRC_DIR)/$(notdir $@)) -o $@

clean:
	del /Q ..\$(notdir $(BUILD_DIR))\*.*
#USE THIS FOR OTHER THAN WINDOW $(RM) $(BUILD_DIR)\*.*