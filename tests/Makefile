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
#   all / test		- Build and run all libraries tests.
#	test_tetris 	- Build and run te-tris library tests.
#   gcov_report		- Create a html report of the executed tests.
#   report			- Create a html report of the executed tests and open it in the default browser.
#   clean    		- Removes all build artifacts and created files.
#   valgrind		- Run all tests with valgrind and write the results to a file.
#   style_check    	- Runs a style check of test code files.
# 	style_make		- Change code so it passes style checks (Google st.).
# 	cpp_check		- Check the test files code with CppCheck tool.
#	help 			- List of targets.
#
# Usage:
#   make target
# ----------------------------------------------------------------------
OS=$(shell uname)
MAKE = make --no-print-directory

# Compillers
C = gcc
CC = g++

# Flags
LAN_FLAGS_C = -std=c11
LAN_FLAGS_CC = -std=c++17

DEBUG_FLAGS = -Wall -Wextra -Werror
POSIX_FLAG = -D_POSIX_C_SOURCE=201706L

INFO_FLAGS = -g -O0
COV_FLAGS =-fprofile-arcs -ftest-coverage


CHECK_LIB = -lcheck
MATH_LIB = -lm
GTEST_LIB = -L/usr/lib/ -lgtest -lgtest_main -pthread #-Wl,--no-warn-search-mismatch

LIB_FLAGS= 
ifeq ($(OS), Linux)
	LIB_FLAGS += -lsubunit
endif

# Checkers
VALG = valgrind --tool=memcheck  --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose 
CLANG = clang-format --style=Google
CPPCHECK = cppcheck --enable=all --suppress=missingIncludeSystem  --force --check-level=exhaustive
VALG_FILE_FIRST_FLAG = --log-file=$(BUILD_DIR)/VALGRIND_tetris.txt
VALG_FILE_SECOND_FLAG = --log-file=$(BUILD_DIR)/VALGRIND_snake.txt
# CPPCHECK_FILE_FIRST_FLAG = --checkers-report=$(BUILD_DIR)/CPPCHECK_test_tetris.txt
# CPPCHECK_FILE_SECOND_FLAG = --checkers-report=$(BUILD_DIR)/CPPCHECK_test_snake.txt

# directories 
ROOT_DIR = ..
SRC_DIR=$(ROOT_DIR)/src
TEST_DIR=$(ROOT_DIR)/tests
BUILD_DIR = $(ROOT_DIR)/build
OBJ_DIR = $(BUILD_DIR)/service_files
BUILD_TEST_DIR = $(BUILD_DIR)/tests
BUILD_COV_DIR = $(BUILD_DIR)/coverage

FIRST_DIR=$(SRC_DIR)/brick_game/tetris
SECOND_DIR=$(SRC_DIR)/brick_game/snakes

# game files
MAIN_EXE = game_5
DATA_FILE_FIRST = high_score_$(FIRST).txt
DATA_FILE_SECOND = high_score_$(SECOND).txt

#game list & files
FIRST = tetris
FIRST_TEST = tetris_test
FIRST_COV = tetris_cov
FIRST_LIB = $(BUILD_DIR)/$(FIRST).a
FIRST_TEST_SRC_FILES=$(FIRST_TEST)s.c
SECOND = snake
SECOND_TEST = snake_test
SECOND_LIB = $(BUILD_DIR)/$(SECOND).a
SECOND_TEST_SRC_FILES = $(SECOND_TEST)s.cc

# extra files
DOXYFILE = $(ROOT_DIR)/materials/Doxyfile

# target specific variables
$(FIRST_TEST): MAIN_FLAGS:= $(LAN_FLAGS_C) $(POSIX_FLAG) $(DEBUG_FLAGS) 
$(FIRST_TEST): LIB_FLAGS:= $(CHECK_LIB) $(LIB_FLAGS) $(MATH_LIB)
$(FIRST_TEST): CC:= $(C)

first_cov: MAIN_FLAGS:= $(LAN_FLAGS_C) $(POSIX_FLAG) $(DEBUG_FLAGS) $(INFO_FLAGS) $(COV_FLAGS)
first_cov: LIB_FLAGS:= $(CHECK_LIB) $(LIB_FLAGS) $(MATH_LIB)
first_cov: CC:= $(C)
# ----------------------------------------------------------------------
# targets
.PHONY: all

all: test

# libraries
.PHONY: $(FIRST) $(SECOND)

$(FIRST):
	@cd $(FIRST_DIR) && $(MAKE) all

$(FIRST_COV):
	@cd $(FIRST_DIR) && $(MAKE) cov

$(SECOND):
	@cd $(SECOND_DIR) && $(MAKE) all

# tests
.PHONY: test test_tetris #test_snake

$(FIRST_TEST):clean $(BUILD_TEST_DIR) $(FIRST)
	$(CC) $(MAIN_FLAGS) $(FIRST_TEST_SRC_FILES) -o $(BUILD_TEST_DIR)/$@ $(FIRST_LIB) $(LIB_FLAGS)
	@rm -fr $(FIRST_LIB)

test_tetris: $(FIRST_TEST)
	@cd $(BUILD_TEST_DIR) && ./$(FIRST_TEST)

test: test_tetris #test_snake

# coverage & report
.PHONY:  gcov_report #s_cov_main 

first_cov:clean $(BUILD_COV_DIR) $(FIRST_COV)
	$(CC) $(MAIN_FLAGS) $(FIRST_TEST_SRC_FILES) -o $(BUILD_COV_DIR)/$@ $(FIRST_LIB) $(LIB_FLAGS)
	@rm -fr $(FIRST_LIB)

first_cov_exe: first_cov
	@cd $(BUILD_COV_DIR) && ./first_cov

first_cov_main: first_cov_exe clean_cov 
	@$(MAKE) $(BUILD_COV_DIR)
	lcov --capture --directory $(OBJ_DIR) --output-file $(BUILD_COV_DIR)/coverage.info
	genhtml --output-directory=$(BUILD_COV_DIR) $(BUILD_COV_DIR)/coverage.info
	@$(MAKE) clean_o

gcov_report: first_cov_main

report: 
	@if [ ! -f $(BUILD_COV_DIR)/index.html ]; then \
    	$(MAKE) gcov_report; \
	fi
	@if [ "$(OS)" = "Linux" ]; then \
		xdg-open $(BUILD_COV_DIR)/index.html; \
	elif [ "$(OS)" = "Darwin" ]; then \
		open $(BUILD_COV_DIR)/index.html; \
	fi

#checkers 
.PHONY:  style_make style_check cpp_check valgrind_test

style_make:
	$(CLANG) -i $(shell find . -type f -name '*.cc' -o -name '*.hpp' -o -name '*.tpp' -o -name '*.h' -o -name '*.c')

style_check: 
	$(CLANG) -n $(shell find . -type f -name '*.cc' -o -name '*.hpp' -o -name '*.tpp' -o -name '*.h' -o -name '*.c')

cpp_check:
	$(CPPCHECK) $(CPPCHECK_FILE_FIRST_FLAG) $(FIRST_TEST_SRC_FILES)
	$(CPPCHECK) $(CPPCHECK_FILE_SECOND_FLAG) $(SECOND_TEST_SRC_FILES)

valgrind_test: $(FIRST_TEST)
	$(VALG) $(VALG_FILE_FIRST_FLAG) ./$(BUILD_TEST_DIR)/$(FIRST_TEST)
#	@cd $(BUILD_COV_DIR) && $(VALG) $(VALG_FILE_SECOND_FLAG) ./$(SECOND_TEST)

# service
.PHONY: clean help

$(BUILD_DIR) $(BUILD_COV_DIR) $(BUILD_TEST_DIR) $(OBJ_DIR):
	@mkdir -p $@

clean_cov:
	@rm -fr $(BUILD_COV_DIR)

clean_o: 
	@rm -fr $(OBJ_DIR)

clean:
	@rm -fr $(BUILD_DIR) $(BUILD_COV_DIR)
	
help target:
	@echo "Main targets are: \n\
	all  \n\
	test \n\
	test_tetris \n\
	gcov_report  \n\
	report  \n\
	style_make  \n\
	style_check  \n\
	cpp_check  \n\
	valgrind \n\
	clean  \n\
	help"	
