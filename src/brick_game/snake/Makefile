# ----------------------------------------------------------------------
# Makefile for The S-Snake
# ----------------------------------------------------------------------
#
# Purpose:
#   This Makefile automates the build, clean, some checks and 
#	documentation creation for The S-Snake game library. 
#
# Notes:
#	After building the library file will be located in the build folder 
#   of the project. Do not forget to adjust a root dir variable if it 
#	is required.
#
# Key Targets:
#   all / s-snake.a	- Builds the libraty (default target).
#	cov				- create a version of library for coverage check.
#   clean    		- Removes all build artifacts.
#   style_check    	- Runs a style check of the library code.
# 	style_make		- Change code so it passes style checks (Google st.).
# 	cpp_check		- Check the library code with CppCheck tool.
#!   dvi    			- Creates documentation for the library.
#	clean_div		- Removes documentation artifacts.
#	rebuild_lib		- Rebuild the library.
#	help 			- List of targets.
#
# Usage:
#   make target
# ----------------------------------------------------------------------

OS=$(shell uname)
SELF = @$(MAKE) --no-print-directory 

# Compillers
CPP = g++

# Flags
CPP_FLAG = -std=c++17

DEBUG_FLAGS = -Wall -Wextra -Werror -I$(SRC_DIR)
POSIX_FLAG = -D_POSIX_C_SOURCE=201706L

INFO_FLAGS = -g -O0
COV_FLAGS =-fprofile-arcs -ftest-coverage

CHLIB = -lcheck
MATHLIB = -lm

LIB_FLAGS= 
ifeq ($(OS), Linux)
	LIB_FLAGS += -lsubunit
endif

# Checkers
# Valgrind check can be found in test file
CPPCHECK = cppcheck --enable=all --suppress=missingIncludeSystem  --force --check-level=exhaustive #--checkers-report=$(CPPCHECK_FILE) 
CLANG = clang-format --style=Google

# directories 
SRC_DIR = game_src
ROOT_DIR = ../../..
BUILD_DIR = $(ROOT_DIR)/build
TEST_DIR=$(ROOT_DIR)/tests
OBJ_DIR = $(BUILD_DIR)/service_files
BUILD_COV_DIR = $(BUILD_DIR)/coverage

CPPCHECK_FILE = $(BUILD_DIR)/RESULT_CPPCHECK_te-tris.txt
GEN_DOC_DIR = $(ROOT_DIR)/materials/gen_docs

# src files
MAIN_HEADER=s-snake.hpp
SRC_FILES = $(shell find . -type  f -name '*.cpp')
SRC_FILES := $(patsubst ./%, %, $(SRC_FILES))
HEAD_FILES = $(shell find . -type f -name '*.hpp')
HEAD_FILES := $(patsubst ./%, %, $(HEAD_FILES))

# gen files
OBJ_FILES = $(addprefix $(OBJ_DIR)/,  $(SRC_FILES:.cpp=.o))
LIB_NAME=$(MAIN_HEADER:.hpp=.a)

# extra files
DOXYFILE = $(ROOT_DIR)/materials/Doxyfile

# target specific variables
$(LIB_NAME): MAIN_FLAGS:= $(CPP_FLAG) $(DEBUG_FLAGS) $(POSIX_FLAG)
cov: MAIN_FLAGS:= $(CPP_FLAG) $(DEBUG_FLAGS) $(POSIX_FLAG) $(INFO_FLAGS) $(COV_FLAGS)

# ----------------------------------------------------------------------
# targets
.PHONY: all

all: $(LIB_NAME)

# library
.PHONY: $(LIB_NAME)
$(LIB_NAME): clean_o $(OBJ_DIR) $(OBJ_FILES)
	@ar rcs $@ $(OBJ_FILES) 
	@mv  $(LIB_NAME) $(BUILD_DIR)/$(LIB_NAME) 
	$(SELF) clean_o         

# coverage library
.PHONY: cov
cov: clean_o $(OBJ_DIR) $(OBJ_FILES) $(BUILD_COV_DIR)
	@ar rcs $(LIB_NAME) $(OBJ_FILES) 
	@mv  $(LIB_NAME) $(BUILD_DIR)/$(LIB_NAME) 

# object files
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CPP) $(MAIN_FLAGS) -c $< -o $@

#checkers 
.PHONY: style_make style_check cpp_check
style_make:
	$(CLANG) -i $(HEAD_FILES) $(SRC_FILES)

style_check: 
	$(CLANG) -n $(HEAD_FILES) $(SRC_FILES)

cpp_check:
	$(CPPCHECK) $(HEAD_FILES) $(SRC_FILES)

# documentation
.PHONY: dvi 
dvi:
	@doxygen $(DOXYFILE) 
	@echo "project documentation can be found in $(GEN_DOC_DIR)"

# service
.PHONY: clean clean_div rebuild_lib help

$(OBJ_DIR) $(BUILD_DIR) $(BUILD_COV_DIR) $(GEN_DOC_DIR):
	@mkdir -p $@

clean_o: 
	@rm -fr $(OBJ_DIR)

clean_div:
	@rm -fr $(GEN_DOC_DIR)

clean: clean_o clean_div
	@rm -fr $(BUILD_DIR)

clear: clean

rebuild_lib: clean all

help target:
	@echo "Main targets are: \n\
	all  \n\
	$(LIB_NAME) \n\
	style_make  \n\
	style_check  \n\
	cpp_check  \n\
	dvi  \n\
	clean  \n\
	clean_div  \n\
	rebuild_lib \n\
	help"
	