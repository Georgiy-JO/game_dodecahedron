# ----------------------------------------------------------------------
# Makefile for The Te-tris
# ----------------------------------------------------------------------
#
# Purpose:
#   This Makefile automates the build, clean, some checks and 
#	documentation creation for The Te-Tris game library. 
#
# Notes:
#	After building the library file will be located in the build folder 
#   of the project. DO not forget to adjust a root dir variable if it 
#	is required.
#
# Key Targets:
#   all / tetris.a	- Builds the libraty (default target).
#	cov				- create a version of library for coverage check.
#   clean    		- Removes all build artifacts.
#   style_check    	- Runs a style check of the library code.
# 	style_make		- Change code so it passes style checks (Google st.).
# 	cpp_check		- Check the library code with CppCheck tool.
#	help 			- List of targets.
#
# Usage:
#   make target
# ----------------------------------------------------------------------

SELF = @$(MAKE) --no-print-directory 

# Compillers
C = gcc

# Flags
LAN_FLAGS_C = -std=c17

DEBUG_FLAGS = -Wall -Wextra -Werror
POSIX_FLAG = -D_POSIX_C_SOURCE=201706L

INFO_FLAGS = -g -O0
COV_FLAGS =-fprofile-arcs -ftest-coverage

# Checkers
# Valgrind check can be found in test file
CPPCHECK = cppcheck --enable=all --suppress=missingIncludeSystem  --force --check-level=exhaustive 
CLANG = clang-format --style=Google

# directories 
ROOT_DIR = ../../..
BUILD_DIR = $(ROOT_DIR)/build
OBJ_DIR = $(BUILD_DIR)/service_files
BUILD_COV_DIR = $(BUILD_DIR)/coverage

# src files
MAIN_HEADER=tetris.h
SRC_FILES = $(shell find . -type  f -name '*.c')
SRC_FILES := $(patsubst ./%, %, $(SRC_FILES))
HEAD_FILES = $(shell find . -type f -name '*.h')
HEAD_FILES := $(patsubst ./%, %, $(HEAD_FILES))

# gen files
OBJ_FILES = $(addprefix $(OBJ_DIR)/,  $(SRC_FILES:.c=.o))
LIB_NAME=$(MAIN_HEADER:.h=.a)

# extra files
DOXYFILE = $(ROOT_DIR)/materials/Doxyfile

# target specific variables
$(LIB_NAME): MAIN_FLAGS:= $(LAN_FLAGS_C) $(DEBUG_FLAGS) $(POSIX_FLAG)
cov: MAIN_FLAGS:= $(LAN_FLAGS_C) $(DEBUG_FLAGS) $(POSIX_FLAG) $(INFO_FLAGS) $(COV_FLAGS)

# ----------------------------------------------------------------------
# targets
.PHONY: all

all: $(LIB_NAME)

# library
.PHONY: $(LIB_NAME)
$(LIB_NAME): clear_o $(OBJ_DIR) $(OBJ_FILES)
	@ar rcs $@ $(OBJ_FILES) 
	@mv  $(LIB_NAME) $(BUILD_DIR)/$(LIB_NAME) 
	$(SELF) clear_o         

# coverage library
.PHONY: cov
cov: clear_o $(OBJ_DIR) $(OBJ_FILES) $(BUILD_COV_DIR)
	@ar rcs $(LIB_NAME) $(OBJ_FILES) 
	@mv  $(LIB_NAME) $(BUILD_DIR)/$(LIB_NAME) 

# object files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(C) $(MAIN_FLAGS) -c $< -o $@

#checkers 
.PHONY: style_make style_check cpp_check
style_make:
	$(CLANG) -i $(HEAD_FILES) $(SRC_FILES)

style_check: 
	$(CLANG) -n $(HEAD_FILES) $(SRC_FILES)

cpp_check:
	$(CPPCHECK) $(HEAD_FILES) $(SRC_FILES)

# service
.PHONY: clean help

$(OBJ_DIR) $(BUILD_DIR) $(BUILD_COV_DIR):
	@mkdir -p $@

clear_o: 
	@rm -fr $(OBJ_DIR)

clear: clear_o 
	@rm -fr $(BUILD_DIR)

clean: clear

help target:
	@echo "Main targets are: \n\
	all  \n\
	$(LIB_NAME) \n\
	style_make  \n\
	style_check  \n\
	cpp_check  \n\
	dvi  \n\
	clean  \n\
	help"
	