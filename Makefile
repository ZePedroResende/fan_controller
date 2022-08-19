SHELL       = /bin/sh
detected_OS := $(shell sh -c 'uname -s 2>/dev/null || echo not')
BIN_NAME    = fan_controller
CC          = g++
LD          = g++
CFLAGS      = -std=c++23 -Wall -Wextra -Wno-unused-parameter -pedantic

ifeq ($(DEBUG), yes)
	CFLAGS += -O0 -g
else
	CFLAGS += -O2
endif

SRC_DIR    = src
BIN_DIR    = bin
BUILD_DIR  = build
SRC        = $(wildcard $(SRC_DIR)/*.cpp)
OBJ        = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))
DEPS       = $(patsubst $(BUILD_DIR)/%.o,$(BUILD_DIR)/%.d,$(OBJ))
PROGRAM    = program

vpath %.cpp $(SRC_DIR)

# ____  _     _    _________
#/  __\/ \ /\/ \  /  __/ ___\
#|  \/|| | ||| |  |  \ |    \
#|    /| \_/|| |_/\  /_\___ |
#\_/\_\\____/\____|____\____/

.DEFAULT_GOAL = all

.PHONY: run fmt doc checkdirs all clean

$(BUILD_DIR)/%.d: %.cpp
	$(CC) -M $(CFLAGS) $(INCLUDES) $< -o $@

$(BUILD_DIR)/%.o: %.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

$(BIN_DIR)/$(BIN_NAME): $(DEPS) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJ)

run:
	@./$(BIN_DIR)/$(BIN_NAME)

fmt:
	@astyle --style=google -nr *.cpp,*.h

checkdirs:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

all: checkdirs $(BIN_DIR)/$(BIN_NAME)

clean:
	@echo "Cleaning..."
	@echo ""
	@rm -rd $(BUILD_DIR)/* $(BIN_DIR)/*
	@echo ""
	@echo "...✓ done!"

