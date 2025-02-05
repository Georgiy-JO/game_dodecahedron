# ----------------------------------------------------------------------
# Makefile for the Game Dodecahedron
# ----------------------------------------------------------------------
#
# Purpose:
#   This Makefile automates the build, clean, install, uninstall, 
#	distribute, document generration, unit tests and check processes 
#	for the Game Dodecahedron application. It is based at smaller 
#	Makefiles of libraries (parts of the project) and tests Makefile.
#
# Notes:
#	Icluded games: tetris, snake.
#	
#
# Key Targets:
#   all / tetris.a	- Builds the libraty (default target).
#
# Usage:
#   make target
# ----------------------------------------------------------------------



# main info
PROJECT_NAME=game_dodecahedron
VERSION =0.1

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

COV_FLAGS =-fprofile-arcs -ftest-coverage

CHECK_LIB = -lcheck
MATH_LIB = -lm
GTEST_LIB = -L/usr/lib/ -lgtest -lgtest_main -pthread #-Wl,--no-warn-search-mismatch

NCURSES_LIB = -lncurses

LIB_FLAGS= 
ifeq ($(OS), Linux)
	LIB_FLAGS += -lsubunit
endif

# Checkers
CPPCHECK = cppcheck --enable=all --suppress=missingIncludeSystem  --force --check-level=exhaustive #--checkers-report=$(CPPCHECK_FILE) 
CLANG = clang-format --style=Google

# directories 
ROOT_DIR = ..
SRC_DIR=$(ROOT_DIR)/src
TEST_DIR=$(ROOT_DIR)/tests
BUILD_DIR = $(ROOT_DIR)/build
# OBJ_DIR = $(BUILD_DIR)/service_files
# COV_DIR = $(BUILD_DIR)/coverage

FIRST_DIR=$(SRC_DIR)/brick_game/tetris
SECOND_DIR=$(SRC_DIR)/brick_game/snake
TUI_DIR = $(SRC_DIR)/gui/cli
GUI_DIR = $(SRC_DIR)/src/gui/desktop

GUI_EXE_DIR = $(BUILD_DIR)/Game_GUI
TUI_EXE_DIR = $(BUILD_DIR)/Game_TUI
GUI_SAVE_DIR = $(GUI_EXE_DIR)/saves
TUI_SAVE_DIR = $(TUI_EXE_DIR)/saves
GENDOC_DIR = $(ROOT_DIR)/materials/gen_docs

DIR ?= $(BUILD_DIR)
DIST_DIR = $(DIR)/distribution

# src files
TUI_HEADER=$(TUI_DIR)/tui.h
TUI_SRC_FILES = $(shell find $(TUI_DIR)/ -type  f -name '*.c')
TUI_SRC_FILES := $(patsubst ./%, %, $(TUI_SRC_FILES))
TUI_HEAD_FILES = $(shell find $(TUI_DIR)/ -type f -name '*.h')
TUI_HEAD_FILES := $(patsubst ./%, %, $(TUI_HEAD_FILES))
GUI_HEADER=$(GUI_DIR)/gui.h
GUI_SRC_FILES = $(shell find $(GUI_DIR)/ -type  f -name '*.c')
GUI_SRC_FILES := $(patsubst ./%, %, $(GUI_SRC_FILES))
GUI_HEAD_FILES = $(shell find $(GUI_DIR)/ -type f -name '*.h')
GUI_HEAD_FILES := $(patsubst ./%, %, $(GUI_HEAD_FILES))

# gen files
CPPCHECK_FILE_tui = $(BUILD_DIR)/RESULT_CPPCHECK_tui.txt
CPPCHECK_FILE_gui = $(BUILD_DIR)/RESULT_CPPCHECK_gui.txt

# game files
MAIN_EXE = game_5
DATA_FILE_FIRST = high_score_$(FIRST).txt
DATA_FILE_SECOND = high_score_$(SECOND).txt

#game list
FIRST = tetris
FIRST_TEST = tetris_test
FIRST_LIB = $(BUILD_DIR)/$(FIRST).a
SECOND = snake
SECOND_TEST = snake_test
SECOND_LIB = $(BUILD_DIR)/$(SECOND).a

# extra files
DOXYFILE = $(ROOT_DIR)/materials/Doxyfile

# target specific variables
install_tui: MAIN_FLAGS:= $(LAN_FLAGS_C) $(POSIX_FLAG) $(DEBUG_FLAGS) 
install_tui: LIB_FLAGS:= $(LIB_FLAG) $(NCURSES_LIB)
install_tui: CC:= $(C)
install_tui: SAVE_DIR= $(TUI_SAVE_DIR)
install_tui uninstall_tui run_tui: DIR:= $(TUI_EXE_DIR)

cpp_check_tui: CPPCHECK:= $(CPPCHECK) --checkers-report=$(CPPCHECK_FILE_tui)
cpp_check_gui: CPPCHECK:= $(CPPCHECK) --checkers-report=$(CPPCHECK_FILE_gui)

# ----------------------------------------------------------------------
# targets
.PHONY: all

all: install run

# libraries
.PHONY: $(FIRST) $(SECOND)

$(FIRST):
	@cd $(FIRST_DIR) && $(MAKE) all

$(SECOND):
	@cd $(SECOND_DIR) && $(MAKE) all

# tests
.PHONY: test $(FIRST_TEST) $(SECOND_TEST)

# the gui part
.PHONY: install_gui run_gui uninstall_gui

# the tui part
.PHONY: intrall_tui run_tui uninstall_tui

install_tui:$(TUI_SAVE_DIR) $(DATA_FILE_FIRST) $(DATA_FILE_SECOND) $(FIRST)#$(SECOND)
	$(CC) $(MAIN_FLAGS) $(TUI_SRC_FILES) -o $(TUI_EXE_DIR)/$(MAIN_EXE)  $(FIRST_LIB) $(LIB_FLAGS)
	@rm -fr $(FIRST_LIB)
	@if [ "$(DIR)" != "$(TUI_EXE_DIR)" ]; then \
		mkdir -p $(DIR); \
		mv $(TUI_EXE_DIR)/* $(DIR)/; \
		echo "rm -fr *" > $(DIR)/uninstall.sh; \
		$(MAKE) clean_tui; \
	fi
	@echo "\n\nTUI version is installed in" && cd $(DIR) && pwd

uninstall_tui: 
	rm -fr $(DIR)

run_tui: 
	@cd $(DIR) && ./$(MAIN_EXE)

rebuild_tui: clean_tui tui

rerun_tui: rebuild_tui run 

# checkers 
.PHONY: style_make style_check cpp_check
style_make:
	$(CLANG) -i $(shell find . -type f -name '*.cc' -o -name '*.hpp' -o -name '*.tpp' -o -name '*.h' -o -name '*.c')

style_check: 
	$(CLANG) -n $(shell find . -type f -name '*.cc' -o -name '*.hpp' -o -name '*.tpp' -o -name '*.h' -o -name '*.c')

cpp_check_tui:
	$(CPPCHECK) $(TUI_HEAD_FILES) $(TUI_SRC_FILES)

cpp_check_gui:
	$(CPPCHECK) $(GUI_HEAD_FILES) $(GUI_SRC_FILES)	

cpp_check: cpp_check_tui cpp_check_gui
	@cd $(FIRST_DIR) && $(MAKE) cpp_check

# 				Valgrind check

# documentation

# distribution

# .PHONY: dist

# dist: $(DIST_DIR) $(TETRIS_DIR) $(GUI_DIR) $(DOC_DIR)
# 	tar -czf $(DIST_DIR)/$(PROJECT_NAME)-$(VERSION).tar.gz $(TETRIS_DIR) $(GUI_DIR) $(DOC_DIR) Makefile

# dist_all: $(DIST_DIR) $(TEST_DIR) $(TETRIS_DIR) $(GUI_DIR)
# 	tar -czf $(DIST_DIR)/$(PROJECT_NAME)-$(VERSION)-f.tar.gz $(TEST_DIR) $(TETRIS_DIR) $(GUI_DIR) $(DOC_DIR) Makefile


# service
.PHONY: clean

$(BUILD_DIR) $(GUI_EXE_DIR) $(TUI_EXE_DIR) $(TUI_SAVE_DIR) $(GUI_SAVE_DIR) $(GENDOC_DIR) $(DIST_DIR) :
	@mkdir -p $@

$(DATA_FILE_FIRST) $(DATA_FILE_SECOND): $(SAVE_DIR)
	@touch $(SAVE_DIR)/$@

clean_tui: 
	@rm -fr $(TUI_EXE_DIR)

clean:
	@rm -fr $(BUILD_DIR) $(GENDOC_DIR) $(DIST_DIR) $(DIR) 









