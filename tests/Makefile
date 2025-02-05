OS=$(shell uname)
# ----------------------------------------------------------------------
# Makefile for tests of the game libraries
# ----------------------------------------------------------------------
#
# Purpose:
#   This Makefile automates buildint and runnin unit tests for the game
#	libraries this project contains. Furthermore, it contains goals for
#	the Valgring check and creating the report of the executed tests.
#
# Key Targets:
#   all / tetris.a	- Builds the libraty (default target).
#
# Usage:
#   make target
# ----------------------------------------------------------------------

MAKE = make --no-print-directory

# Compillers
C = gcc
CC = g++

# Flags
LAN_FLAGS_C = -std=c11
LAN_FLAGS_CC = -std=c++17

DEBUG_FLAGS = -Wall -Wextra -Werror
POSIX_FLAG = -D_POSIX_C_SOURCE=201706L

VALG_FLAGS = -g
COV_FLAGS =-fprofile-arcs -ftest-coverage

CHECK_LIB = -lcheck
MATH_LIB = -lm
GTEST_LIB = -L/usr/lib/ -lgtest -lgtest_main -pthread #-Wl,--no-warn-search-mismatch

LIB_FLAGS= 
ifeq ($(OS), Linux)
	LIB_FLAGS += -lsubunit
endif

# Checkers
VALG = valgrind --tool=memcheck  --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=$(VALG_FILE) ./
CLANG = clang-format --style=Google

# directories 
ROOT_DIR = ..
SRC_DIR=$(ROOT_DIR)/src
TEST_DIR=$(ROOT_DIR)/tests
BUILD_DIR = $(ROOT_DIR)/build
OBJ_DIR = $(BUILD_DIR)/service_files
COV_DIR = $(BUILD_DIR)/coverage

FIRST_DIR=$(SRC_DIR)/brick_game/tetris
SECOND_DIR=$(SRC_DIR)/brick_game/snakes

# gen files
VALG_FILE = $(BUILD_DIR)/RESULT_VALGRIND_ui.txt
CPPCHECK_FILE_tui = $(BUILD_DIR)/RESULT_CPPCHECK_tui.txt
CPPCHECK_FILE_gui = $(BUILD_DIR)/RESULT_CPPCHECK_gui.txt

# game files
MAIN_EXE = game_5
DATA_FILE_FIRST = high_score_$(FIRST).txt
DATA_FILE_SECOND = high_score_$(SECOND).txt

#game list & files
FIRST = tetris
FIRST_TEST = tetris_test
FIRST_LIB = $(BUILD_DIR)/$(FIRST).a
FIRST_TEST_SRC_FILES=$(FIRST_TEST)s.c
SECOND = snake
SECOND_TEST = snake_test
SECOND_LIB = $(BUILD_DIR)/$(SECOND).a
SECOND_TEST_SRC_FILES = $(SECOND_TEST)s.cc

# extra files
DOXYFILE = $(ROOT_DIR)/materials/Doxyfile

# target specific variables
$(FIRST_TEST): MAIN_FLAGS:= $(LAN_FLAGS_C) $(POSIX_FLAG) $(DEBUG_FLAGS) #$(VALG_FLAGS)
$(FIRST_TEST): LIB_FLAGS:= $(LIB_FLAGS) $(CHECK_LIB) $(MATH_LIB)
$(FIRST_TEST): CC:= $(C)


# ----------------------------------------------------------------------
# targets
.PHONY: all

all: test

# libraries
.PHONY: $(FIRST) $(SECOND)

$(FIRST):
	@cd $(FIRST_DIR) && $(MAKE) all

$(SECOND):
	@cd $(SECOND_DIR) && $(MAKE) all

# tests
.PHONY: test test_tetris test_snake

$(FIRST_TEST):$(BUILD_DIR) $(FIRST)
	$(CC) $(MAIN_FLAGS) $(FIRST_TEST_SRC_FILES) -o $(BUILD_DIR)/$@ $(FIRST_LIB) $(LIB_FLAGS)
#	@rm -fr $(FIRST_LIB)

test_tetris: $(FIRST_TEST)
	@cd $(BUILD_DIR) && ./$(FIRST_TEST)

test: test_tetris




# service
.PHONY: clean

$(BUILD_DIR) $(COV_DIR):
	@mkdir -p $@

clean:
	@rm -fr $(BUILD_DIR) $(COV_DIR)