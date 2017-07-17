######################################################################################
# First Make
######################################################################################
ifeq ("x", "y")	# Comment Start
CC := gcc
CXX := g++
CXXFLAGS := -std=c++11 -g -Wall

BUILD_DIR = ..\build
SRC_DIR = .\src
INC_DIR = .\include

INC_FLAGS = $(addprefix -I,$(INC_DIR))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

SRCS := $(wildcard src/*.cpp)
OBJS_FILES := $(notdir $(SRCS))
OBJS = $(patsubst %.cpp, $(BUILD_DIR)\\%.o, $(OBJS_FILES))
DEPS := $(OBJS:.o=.d)

TARGET_EXEC = main.exe

#$(BUILD_DIR)\$(TARGET_EXEC): $(OBJS)
#	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# c++ source
$(BUILD_DIR)\%.cpp.o: $(SRCS)
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -f $(BUILD_DIR)\*.o $(BUILD_DIR)\*.exe

-include $(DEPS)

MKDIR_P ?= mkdir -p
endif	#Commnet End


######################################################################################
# Second Make
######################################################################################

CXX = g++
CXXFLAGS = -std=c++11 -g -Wall
INCLUDES = .\include

BUILD = ..\build
SRC = .\src

SOURCES = $(wildcard src/*.cpp)

OBJS_FILES = $(notdir $(SOURCES))
OBJS = $(patsubst %.cpp, $(BUILD)\\%.o, $(OBJS_FILES))

INC_FLAGS = $(addprefix -I,$(INCLUDES))
CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

MAIN = main

.PHONY: all run clean

$(MAIN): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm -f $(BUILD)\*.o $(BUILD)\*.exe