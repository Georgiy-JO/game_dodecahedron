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
#	test_first 	- Build and run te-tris library tests.
#	test_second	- Build and run snake library tests.
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
C_FLAG = -std=c11
CC_FLAG = -std=c++17

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
VALG_FILE_FIRST_FLAG = --log-file=VALGRIND_tetris.txt
VALG_FILE_SECOND_FLAG = --log-file=VALGRIND_snake.txt
# CPPCHECK_FILE_FIRST_FLAG = --checkers-report=$(BUILD_DIR)/CPPCHECK_test_first.txt
# CPPCHECK_FILE_SECOND_FLAG = --checkers-report=$(BUILD_DIR)/CPPCHECK_test_second.txt

# directories 
ROOT_DIR = ..
SRC_DIR=$(ROOT_DIR)/src
TEST_DIR=$(ROOT_DIR)/tests
BUILD_DIR = $(ROOT_DIR)/build
OBJ_DIR = $(BUILD_DIR)/service_files
BUILD_TEST_DIR = $(BUILD_DIR)/tests
BUILD_COV_DIR = $(BUILD_DIR)/coverage

SAVE_TEST_DIR = $(BUILD_TEST_DIR)/saves
SAVE_COV_DIR = $(BUILD_COV_DIR)/saves
DATA_FILE_FIRST = high_score_$(FIRST).txt
DATA_FILE_SECOND = high_score_$(SECOND).txt

FIRST_DIR=$(SRC_DIR)/brick_game/tetris
SECOND_DIR=$(SRC_DIR)/brick_game/snake

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
SECOND = s-snake
SECOND_TEST = s-snake_test
SECOND_COV = s-snake_cov
SECOND_LIB = $(BUILD_DIR)/$(SECOND).a
SECOND_TEST_SRC_FILES = $(SECOND_TEST)s.cpp

# extra files
DOXYFILE = $(ROOT_DIR)/materials/Doxyfile

# target specific variables
$(FIRST_TEST): MAIN_FLAGS:= $(C_FLAG) $(POSIX_FLAG) $(DEBUG_FLAGS) 
$(FIRST_TEST): LIB_FLAGS:= $(CHECK_LIB) $(LIB_FLAGS) $(MATH_LIB)
$(FIRST_TEST): CC:= $(C)
$(FIRST_TEST): SAVE_DIR:=$(SAVE_TEST_DIR)
$(SECOND_TEST): MAIN_FLAGS:= $(CC_FLAG) $(POSIX_FLAG) $(DEBUG_FLAGS) 
$(SECOND_TEST): LIB_FLAGS:= $(GTEST_LIB)
$(SECOND_TEST): CC:= $(CC)
$(SECOND_TEST): SAVE_DIR:=$(SAVE_TEST_DIR)

first_cov: MAIN_FLAGS:= $(C_FLAG) $(POSIX_FLAG) $(DEBUG_FLAGS) $(INFO_FLAGS) $(COV_FLAGS)
first_cov: LIB_FLAGS:= $(CHECK_LIB) $(LIB_FLAGS) $(MATH_LIB)
first_cov: CC:= $(C)
first_cov: SAVE_DIR:=$(SAVE_COV_DIR)
second_cov: MAIN_FLAGS:= $(CC_FLAG) $(POSIX_FLAG) $(DEBUG_FLAGS) $(INFO_FLAGS) $(COV_FLAGS)
second_cov: LIB_FLAGS:= $(GTEST_LIB)
second_cov: CC:= $(CC)
second_cov: SAVE_DIR:=$(SAVE_COV_DIR)
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

$(SECOND_COV):
	@cd $(SECOND_DIR) && $(MAKE) cov

# tests
.PHONY: test test_first test_second

$(FIRST_TEST):clean $(BUILD_TEST_DIR) $(SAVE_TEST_DIR) $(DATA_FILE_FIRST) $(FIRST)
	@$(CC) $(MAIN_FLAGS) $(FIRST_TEST_SRC_FILES) -o $(BUILD_TEST_DIR)/$@ $(FIRST_LIB) $(LIB_FLAGS)
	@rm -fr $(FIRST_LIB)

test_first: $(FIRST_TEST)
	@cd $(BUILD_TEST_DIR) && ./$(FIRST_TEST)

$(SECOND_TEST):clean $(BUILD_TEST_DIR) $(SAVE_TEST_DIR) $(DATA_FILE_SECOND) $(SECOND)
	@$(CC) $(MAIN_FLAGS) $(SECOND_TEST_SRC_FILES) -o $(BUILD_TEST_DIR)/$@ $(SECOND_LIB) $(LIB_FLAGS)
	@rm -fr $(SECOND_LIB)

test_second: $(SECOND_TEST)
	@cd $(BUILD_TEST_DIR) && ./$(SECOND_TEST)

test: test_first test_second

# coverage & report
.PHONY:  gcov_report  report first_cov_main second_cov_main

first_cov:clean_cov clean_o $(BUILD_COV_DIR) $(SAVE_COV_DIR) $(DATA_FILE_FIRST) $(FIRST_COV)
	@$(CC) $(MAIN_FLAGS) $(FIRST_TEST_SRC_FILES) -o $(BUILD_COV_DIR)/$@ $(FIRST_LIB) $(LIB_FLAGS)
	@rm -fr $(FIRST_LIB)

second_cov:clean_cov clean_o $(BUILD_COV_DIR) $(SAVE_COV_DIR) $(DATA_FILE_SECOND) $(SECOND_COV)
	@$(CC) $(MAIN_FLAGS) $(SECOND_TEST_SRC_FILES) -o $(BUILD_COV_DIR)/$@ $(SECOND_LIB) $(LIB_FLAGS)
	@rm -fr $(SECOND_LIB)

first_cov_exe: first_cov
	@cd $(BUILD_COV_DIR) && ./first_cov

second_cov_exe: second_cov
	@cd $(BUILD_COV_DIR) && ./second_cov

first_cov_main: first_cov_exe
	@lcov --capture --directory $(OBJ_DIR) --output-file $(BUILD_COV_DIR)/coverage.info
	genhtml --output-directory=$(BUILD_COV_DIR) $(BUILD_COV_DIR)/coverage.info
	@$(MAKE) clean_o

second_cov_main: second_cov_exe
	@lcov --capture --directory $(OBJ_DIR) --output-file $(BUILD_DIR)/coverage_2.info
	@lcov --remove $(BUILD_DIR)/coverage_2.info '/usr/*' --output-file $(BUILD_COV_DIR)/coverage.info
	@rm -fr $(BUILD_DIR)/coverage_2.info $(SAVE_COV_DIR)
	genhtml --output-directory=$(BUILD_COV_DIR) $(BUILD_COV_DIR)/coverage.info
	@$(MAKE) clean_o

cov_main: first_cov_exe
	@lcov --capture --directory $(OBJ_DIR) --output-file $(BUILD_DIR)/coverage_1.info
	@$(MAKE) second_cov_exe
	@lcov --capture --directory $(OBJ_DIR) --output-file $(BUILD_DIR)/coverage_2.info
	@lcov --add-tracefile $(BUILD_DIR)/coverage_1.info --add-tracefile $(BUILD_DIR)/coverage_2.info --output-file $(BUILD_COV_DIR)/coverage_unfiltered.info
	@rm -fr $(BUILD_DIR)/coverage_1.info $(BUILD_DIR)/coverage_2.info
	@lcov --remove $(BUILD_COV_DIR)/coverage_unfiltered.info '/usr/*' --output-file $(BUILD_COV_DIR)/coverage.info
	@rm -fr $(BUILD_COV_DIR)/coverage_unfiltered.info $(SAVE_COV_DIR)
	genhtml --output-directory=$(BUILD_COV_DIR) $(BUILD_COV_DIR)/coverage.info
	@$(MAKE) clean_o

gcov_report: clean cov_main

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
.PHONY:  style_make style_check cpp_check valgrind_test valgrind_first valgrind_second

style_make:
	$(CLANG) -i $(shell find . -type f -name '*.cpp' -o -name '*.cc' -o -name '*.hpp' -o -name '*.tpp' -o -name '*.h' -o -name '*.c')

style_check: 
	$(CLANG) -n $(shell find . -type f -name '*.cpp' -o -name '*.cc' -o -name '*.hpp' -o -name '*.tpp' -o -name '*.h' -o -name '*.c')

cpp_check:
	$(CPPCHECK) $(CPPCHECK_FILE_FIRST_FLAG) $(FIRST_TEST_SRC_FILES)
	$(CPPCHECK) $(CPPCHECK_FILE_SECOND_FLAG) $(SECOND_TEST_SRC_FILES)

valgrind_first: $(FIRST_TEST) 
	@cd $(BUILD_TEST_DIR) && $(VALG) $(VALG_FILE_FIRST_FLAG) ./$(FIRST_TEST)

valgrind_second: $(SECOND_TEST)
	@cd $(BUILD_TEST_DIR) && $(VALG) $(VALG_FILE_SECOND_FLAG) ./$(SECOND_TEST) 

valgrind_test: valgrind_first  valgrind_second

# service
.PHONY: clean help

$(BUILD_DIR) $(BUILD_COV_DIR) $(BUILD_TEST_DIR) $(OBJ_DIR) $(SAVE_TEST_DIR) $(SAVE_COV_DIR):
	@mkdir -p $@


$(DATA_FILE_FIRST) $(DATA_FILE_SECOND): $(SAVE_DIR)
	@touch $(SAVE_DIR)/$@


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
	test_first \n\
	test_second \n\
	gcov_report  \n\
	report  \n\
	style_make  \n\
	style_check  \n\
	cpp_check  \n\
	valgrind \n\
	clean  \n\
	help"	
