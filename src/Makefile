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
#   all 			- Install GUI and TUI versions into the default 
#					  	location (/build) and run the GUI version.
#	install			- Install GUI and TUI versions in the default 
#						location (/build). Installation directory can 
#						be set by adding "DIR=pwd/location" to the command).
#	run 			- Run the GUI version.
#	uninstall		- Uninstall the GUI and TUI versions from the 
#						default location only.
#					- Install TUI version in the default location 
#						(/build). Installation directory can be set by
#						adding "DIR=pwd/location" to the command).
#	install_tui_first
#	install_tui_second
#	run_tui 		- Run the TUI version (will work only if it is installed).
#	uninstall_tui	- Uninstall TUI version.
#	install_gui_first
#	install_gui_second
#	run_gui 
#	uninstall_gui
#	test			- Build and run all libraries tests.
#	test_tetris 	- Build and run tetris library tests.
#   gcov_report		- Create a html report of the executed tests.
#   report			- Create a html report of the executed tests and open 
#						it in the default browser.
#   clean    		- Removes all build artifacts and created files.
#   valgrind		- run all tests with valgrind and write the results to a file.
#   style_check    	- Runs a style check of all code files.
# 	style_make		- Change all code files so they passe style checks (Google st.).
# 	cpp_check		- Check all code files with CppCheck tool.
#	help 			- List of targets.
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
CPPCHECK = cppcheck --enable=all --suppress=missingIncludeSystem --force --check-level=exhaustive 
CLANG = clang-format --style=Google

# directories 
ROOT_DIR := $(CURDIR)/..
SRC_DIR=$(ROOT_DIR)/src
TEST_DIR=$(ROOT_DIR)/tests
BUILD_DIR = $(ROOT_DIR)/build

FIRST_DIR=$(SRC_DIR)/brick_game/tetris
SECOND_DIR=$(SRC_DIR)/brick_game/snake
UI_DIR = $(SRC_DIR)/gui
TUI_DIR = $(UI_DIR)/cli
GUI_DIR = $(UI_DIR)/desktop

GUI_EXE_DIR = $(BUILD_DIR)/Game_GUI
TUI_EXE_DIR = $(BUILD_DIR)/Game_TUI
GUI_SAVE_DIR = $(GUI_EXE_DIR)/saves
TUI_SAVE_DIR = $(TUI_EXE_DIR)/saves
GUI_CMAKE_DIR = $(BUILD_DIR)/gui_build
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
GUI_SRC_FILES = $(shell find $(GUI_DIR)/ -type  f -name '*.cpp' -o -name '*.tpp')
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
GUI_DATA_DIR = $(UI_DIR)/data

#game list
FIRST = tetris
FIRST_TEST = test_first
FIRST_LIB = $(BUILD_DIR)/$(FIRST).a
FIRST_FLAG = -DTE_TRIS
SECOND = s-snake
SECOND_TEST = test_second
SECOND_LIB = $(BUILD_DIR)/$(SECOND).a
SECOND_FLAG = -DS_SNAKE

# extra files
DOXYFILE = $(ROOT_DIR)/materials/Doxyfile

# target specific variables
# install_tui: MAIN_FLAGS:= $(LAN_FLAGS_C) $(POSIX_FLAG) $(DEBUG_FLAGS) 
# install_tui: LIB_FLAGS:=$(FIRST_LIB) $(LIB_FLAGS) $(NCURSES_LIB)
# install_tui: CC:= $(C)
install_tui: SAVE_DIR= $(TUI_SAVE_DIR)
install_gui: SAVE_DIR=$(GUI_SAVE_DIR)
install_tui run_tui: DIR:= $(TUI_EXE_DIR)
install_gui run_gui: DIR:=$(GUI_EXE_DIR)
 
install_tui_first install_gui_first: LIB = $(FIRST_LIB)
install_tui_second install_gui_second: LIB = $(SECOND_LIB)

install_tui_first: CC:= $(C)
install_tui_first: LIB_FLAGS:=$(FIRST_LIB) $(LIB_FLAG) $(NCURSES_LIB)
install_tui_first:  MAIN_FLAGS:= $(LAN_FLAGS_C) $(POSIX_FLAG) $(DEBUG_FLAGS) $(FIRST_FLAG)
install_tui_second: CC:=$(CC)
install_tui_second: LIB_FLAGS:=$(SECOND_LIB) $(LIB_FLAGS) $(NCURSES_LIB)
install_tui_second:  MAIN_FLAGS:= $(LAN_FLAGS_CC) $(POSIX_FLAG) $(DEBUG_FLAGS) $(SECOND_FLAG)

install_gui_first: MAIN_FLAGS:= $(FIRST_FLAG)=1
install_gui_second: MAIN_FLAGS:= $(SECOND_FLAG)=1

#cpp_check_tui: CPPCHECK:= $(CPPCHECK) --checkers-report=$(CPPCHECK_FILE_tui)
#cpp_check_gui: CPPCHECK:= $(CPPCHECK) --checkers-report=$(CPPCHECK_FILE_gui)

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

# test and report
.PHONY: test $(FIRST_TEST) $(SECOND_TEST) gcov_report report

test:
	@cd $(TEST_DIR) && $(MAKE) all

$(FIRST_TEST):
	@cd $(TEST_DIR) && $(MAKE) $(FIRST_TEST)

$(SECOND_TEST):
	@cd $(TEST_DIR) && $(MAKE) $(SECOND_TEST)

gcov_report:
	@cd $(TEST_DIR) && $(MAKE) gcov_report

report:
	@cd $(TEST_DIR) && $(MAKE) report

# the tui part
.PHONY: intrall_tui run_tui uninstall_tui  install_tui_first install_tui_second

install_tui:$(TUI_SAVE_DIR) $(DATA_FILE_FIRST) $(DATA_FILE_SECOND) 
	@$(CC) $(MAIN_FLAGS) $(TUI_SRC_FILES) -o $(TUI_EXE_DIR)/$(MAIN_EXE) $(LIB_FLAGS)
	@rm -fr $(LIB)
	@if [ "$(DIR)" != "$(TUI_EXE_DIR)" ]; then \
		mkdir -p $(DIR); \
		mv $(TUI_EXE_DIR)/* $(DIR)/; \
		echo "rm -fr *" > $(DIR)/uninstall.sh; \
		$(MAKE) clean_tui; \
	fi
	@echo "\n\nTUI version is installed in" && cd $(DIR) && pwd

install_tui_first: clean_tui $(FIRST) install_tui

install_tui_second: clean_tui $(SECOND) install_tui

uninstall_tui: 
	rm -fr $(TUI_EXE_DIR)

run_tui: 
	@cd $(DIR) && ./$(MAIN_EXE)

rebuild_tui: clean_tui tui

# the gui part
.PHONY: install_gui run_gui uninstall_gui install_gui_first install_gui_second

install_gui: $(GUI_SAVE_DIR) $(GUI_CMAKE_DIR) $(DATA_FILE_FIRST) $(DATA_FILE_SECOND)
	@cd $(GUI_CMAKE_DIR) && cmake $(GUI_DIR)/  $(MAIN_FLAGS) && make
	@rm -fr $(LIB)
	@cp -r $(GUI_DATA_DIR) $(GUI_EXE_DIR)/data
	@mv $(GUI_CMAKE_DIR)/$(MAIN_EXE) $(GUI_EXE_DIR)/$(MAIN_EXE)
	@rm -fr $(GUI_CMAKE_DIR)
	@if [ "$(DIR)" != "$(GUI_EXE_DIR)" ]; then \
		mkdir -p $(DIR); \
		mv $(GUI_EXE_DIR)/* $(DIR)/; \
		echo "rm -fr *" > $(DIR)/uninstall.sh; \
		$(MAKE) clean_gui; \
	fi
	@echo "\n\nGUI version is installed in" && cd $(DIR) && pwd

install_gui_first: clean_gui $(FIRST) install_gui

install_gui_second: clean_gui $(SECOND) install_gui

uninstall_gui: 
	rm -fr $(GUI_EXE_DIR)

run_gui: 
	@cd $(DIR) && ./$(MAIN_EXE)

# main part
.PHONY:  install run uninstall
install: install_gui_second

run: install run_gui

uninstall: uninstall_gui

# checkers 
.PHONY: style_make style_check cpp_check valgrind
style_make:
	$(CLANG) -i $(shell find ../ -type f -name '*.cpp' -o -name '*.cc' -o -name '*.hpp' -o -name '*.tpp' -o -name '*.h' -o -name '*.c')
	@cd $(TEST_DIR) && $(MAKE) style_make

style_check: 
	$(CLANG) -n $(shell find ../ -type f -name '*.cpp' -o -name '*.cc' -o -name '*.hpp' -o -name '*.tpp' -o -name '*.h' -o -name '*.c')
	@cd $(TEST_DIR) && $(MAKE) style_check

cpp_check_tui:
	$(CPPCHECK) $(TUI_HEAD_FILES) $(TUI_SRC_FILES)

cpp_check_gui:
	$(CPPCHECK) $(GUI_HEAD_FILES) $(GUI_SRC_FILES)	

cpp_check: cpp_check_tui cpp_check_gui
	@cd $(FIRST_DIR) && $(MAKE) cpp_check
	@cd $(SECOND_DIR) && $(MAKE) cpp_check
	@cd $(TEST_DIR) && $(MAKE) cpp_check

valgrind:
	@cd $(TEST_DIR) && $(MAKE) valgrind_test

# service
.PHONY: clean help

$(BUILD_DIR) $(GUI_EXE_DIR) $(TUI_EXE_DIR) $(TUI_SAVE_DIR) $(GUI_SAVE_DIR) $(GENDOC_DIR) $(DIST_DIR) $(GUI_CMAKE_DIR):
	@mkdir -p $@

$(DATA_FILE_FIRST) $(DATA_FILE_SECOND): $(SAVE_DIR)
	@touch $(SAVE_DIR)/$@

clean_tui: 
	@rm -fr $(TUI_EXE_DIR)

clean_gui:
	@rm -fr $(GUI_EXE_DIR)

clean:
	@rm -fr $(BUILD_DIR) $(GENDOC_DIR) $(DIST_DIR) $(DIR) 

help target:
	@echo "Main targets are: \n\
	all  \n\
	install \n\
	run \n\
	uninstall \n\
	install_tui_first \n\
	install_tui_second \n\
	run_tui \n\
	uninstall_tui \n\
	install_gui_first \n\
	install_gui_second \n\
	run_gui \n\
	uninstall_gui \n\
	test \n\
	test_tetris \n\
	gcov_report  \n\
	report  \n\
	style_make  \n\
	style_check  \n\
	cpp_check  \n\
	valgrind \n\
	clean  \n\
	help " 


# documentation

# distribution

# .PHONY: dist

# dist: $(DIST_DIR) $(TETRIS_DIR) $(GUI_DIR) $(DOC_DIR)
# 	tar -czf $(DIST_DIR)/$(PROJECT_NAME)-$(VERSION).tar.gz $(TETRIS_DIR) $(GUI_DIR) $(DOC_DIR) Makefile

# dist_all: $(DIST_DIR) $(TEST_DIR) $(TETRIS_DIR) $(GUI_DIR)
# 	tar -czf $(DIST_DIR)/$(PROJECT_NAME)-$(VERSION)-f.tar.gz $(TEST_DIR) $(TETRIS_DIR) $(GUI_DIR) $(DOC_DIR) Makefile

