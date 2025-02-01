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
#   clean    		- Removes all build artifacts.
#   style_check    	- Runs result of style checks of the library code.
#!   dvi    			- Creates documentation for the library.
#	clean_doc		- Removes documentation artifacts.
# 	style_make		- Change code so it passes style checks (Google st.).
# 	cpp_check		- Check the library code with CppCheck tool.
#	rebuild_lib		- Rebuild the library.
#	help 			- List of targets.
#
# Usage:
#   make target
# ----------------------------------------------------------------------

OS=$(shell uname)
SELF = @$(MAKE) --no-print-directory 

# Compillers
C = gcc

# Flags
LAN_FLAGS_C = -std=c11

DEBUG_FLAGS = -Wall -Wextra -Werror
POSIX_FLAG = -D_POSIX_C_SOURCE=201706L

VALG_FLAGS = -g
COV_FLAGS =-fprofile-arcs -ftest-coverage

CHLIB = -lcheck
MATHLIB = -lm

LIBFLAGS= 
ifeq ($(OS), Linux)
	LIBFLAGS += -lsubunit
endif

# Checkers
# Valgrind check can be found in test file
CPPCHECK = cppcheck --enable=all --suppress=missingIncludeSystem  --force --check-level=exhaustive --checkers-report=$(CPPCHECK_FILE) 
CLANG = clang-format --style=Google

# directories 
ROOT_DIR = ../../..
BUILD_DIR = $(ROOT_DIR)/build
TEST_DIR=$(ROOT_DIR)/tests
OBJ_DIR = $(BUILD_DIR)/service_files
COV_DIR = $(BUILD_DIR)/coverage
CPPCHECK_FILE = $(BUILD_DIR)/RESULT_CPPCHECK_te-tris.txt
GEN_DOC_DIR = $(ROOT_DIR)/materials/gen_docs

# src files
MAIN_HEADER=tetris.h
SRC_FILES = $(shell find . -type  f -name '*.c')
HEAD_FILES = $(shell find . -type f -name '*.h')

# gen files
# OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:.c=.o)))
OBJ_FILES = $(addprefix $(OBJ_DIR)/,  $(SRC_FILES:.c=.o))
LIB_NAME=$(MAIN_HEADER:.h=.a)
LIB_COV_NAME=$(MAIN_HEADER:.h=.cov.a)

# extra files
DOXYFILE = $(ROOT_DIR)/materials/Doxyfile

# target specific variables
$(LIB_NAME): MAIN_FLAGS:= $(LAN_FLAGS_C) $(DEBUG_FLAGS) $(POSIX_FLAG) #$(VALG_FLAGS)
$(LIB_COV_NAME): MAIN_FLAGS:=  $(LAN_FLAGS_C) $(DEBUG_FLAGS) $(POSIX_FLAG) $(COV_FLAGS)

# ----------------------------------------------------------------------
# targets
.PHONY: all

all: $(LIB_NAME)

# library
.PHONY: $(LIB_NAME)
$(LIB_NAME): clear_o $(OBJ_DIR) $(OBJ_FILES)
	ar rcs $@ $(OBJ_FILES) 
	@mv  $(LIB_NAME) $(BUILD_DIR)/$(LIB_NAME) 
	$(SELF) clear_o         

# object files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(C) $(MAIN_FLAGS) -c $< -o $@

# $(OBJ_DIR)/%.o: */%.c
# 	@$(C) $(MAIN_FLAGS) -c $< -o $@

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
.PHONY: clean clean_doc rebuild_lib help

$(OBJ_DIR) $(BUILD_DIR) $(COV_DIR) $(GEN_DOC_DIR):
	@mkdir -p $@

clear_o: 
	@rm -fr $(OBJ_DIR)

clean_doc:
	@rm -fr $(GEN_DOC_DIR)

clear: clear_o clean_doc
	@rm -fr $(BUILD_DIR)

clean: clear

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
	clean_doc  \n\
	rebuild_lib"