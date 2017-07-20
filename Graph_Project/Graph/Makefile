CXX = g++
CXXFLAGS = -std=c++11

INC_DIR = ./include
SRC_DIR = ./src
OUT_DIR = ../build

INCFLAGS = $(addprefix -I,$(INC_DIR))
CPPFLAGS ?= $(INCFLAGS) -MMD -MP

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

CPP_FILES = $(notdir $(SRC_FILES))
OBJ_FILES = $(patsubst %.cpp, $(OUT_DIR)/%.o, $(CPP_FILES))

TARGET = $(OUT_DIR)/main.exe

.PHONY: all clean

MKDIR = mkdir

all:	makeOutDir $(TARGET)

makeOutDir:
	$(MKDIR) ..\$(notdir $(OUT_DIR))

$(TARGET):	$(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ_FILES)

$(OBJ_FILES):
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(patsubst %.o, %.cpp, $(SRC_DIR)/$(notdir $@)) -o $@

clean:
	rd ..\$(notdir $(OUT_DIR))
#del /Q ..\$(notdir $(OUT_DIR))\*.*					# TO DELETE ONLY FILES , /Q quitely
#USE THIS FOR OTHER THAN WINDOW $(RM) $(OUT_DIR)\*.*