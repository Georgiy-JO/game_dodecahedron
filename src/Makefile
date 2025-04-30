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
#	Currrent version icludeds games: tetris (first game), snake (second game).
#	
# Key Targets:
#   all 				- Install GUI versions of the second game into 
#						the default location (/build) and run it.
#	install				- Install GUI versions of the second game into 
#						the default location (/build). 
#						Installation directory can be set by adding 
#						"DIR= pwd/game_folder" to the command.
#	run 				- Run the GUI version of the game (works only 
#						if it is installed).
#	uninstall			- Uninstall the GUI/TUI version from the default 
#						location only.
#	install_tui_first	- Install TUI version of the first game 
#						into the default location (/build). 
#						Installation directory can be set by adding
#						"DIR= pwd/game_folder" to the command.
#	install_tui_second	- Install TUI version of the second game 
#						into the default location (/build). 
#						Installation directory can be set by adding
#						"DIR= pwd/game_folder" to the command.
#	run_tui 			- Run the TUI version (works only if it is installed).
#	uninstall_tui		- Uninstall the TUI version from the default 
#						location only.
#	install_gui_first	- Install GUI version of the first game 
#						into the default location (/build). 
#						Installation directory can be set by adding
#						"DIR= pwd/game_folder" to the command.
#	install_gui_second	- Install GUI version of the second game 
#						into the default location (/build). 
#						Installation directory can be set by adding
#						"DIR= pwd/game_folder" to the command.
#	run_gui 			- Run the GUI version (workso nly if it is installed). 
#	uninstall_gui		- Uninstall the GUI version from the default 
#						location only.
#	test				- Build and run all libraries tests.
#	test_first 			- Build and run first game library tests.
#	test_second 		- Build and run second game library tests.
#   gcov_report			- Create a html report of the executed tests.
#   report				- Create a html report of the executed tests  
#						and open it in the default browser.
#   clean    			- Removes all build artifacts and created files.
#   valgrind			- run all tests with valgrind and write 
#						the results to a file.
#   style_check    		- Runs a style check of all code files.
# 	style_make			- Change all code files so they passe style 
#						checks (Google st.).
# 	cpp_check			- Check all code files with CppCheck tool.
#	dvi					- Create a html code documentation.
#	docs				- Create a html code documentation and open 
#						it in the default browser.
#	dist				- Create an archive for distribution.
#						Distribution directory can be set by adding
#						"DIR=pwd/location" to the command.
#	help 				- List of targets.
#
# Usage:
#   make target
# ----------------------------------------------------------------------



# main info
PROJECT_NAME=game_dodecahedron
VERSION =1.0

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
GENDOC_DIR = $(BUILD_DIR)/gen_doc

DIR ?= $(BUILD_DIR)

# src files
TUI_SRC_FILES = $(shell find $(TUI_DIR)/ -type  f -name '*.c')
TUI_SRC_FILES := $(patsubst ./%, %, $(TUI_SRC_FILES))
TUI_HEAD_FILES = $(shell find $(TUI_DIR)/ -type f -name '*.h')
TUI_HEAD_FILES := $(patsubst ./%, %, $(TUI_HEAD_FILES))
GUI_SRC_FILES = $(shell find $(GUI_DIR)/ -type  f -name '*.cpp' -o -name '*.tpp')
GUI_SRC_FILES := $(patsubst ./%, %, $(GUI_SRC_FILES))
GUI_HEAD_FILES = $(shell find $(GUI_DIR)/ -type f -name '*.h')
GUI_HEAD_FILES := $(patsubst ./%, %, $(GUI_HEAD_FILES))

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
DIST_LIST=$(SRC_DIR) $(TEST_DIR) $(DOXYFILE) $(ROOT_DIR)/materials $(ROOT_DIR)/misc $(ROOT_DIR)/Makefile

# target specific variables
install_tui: SAVE_DIR= $(TUI_SAVE_DIR)
install_gui: SAVE_DIR=$(GUI_SAVE_DIR)
install_tui run_tui: DIR:= $(TUI_EXE_DIR)
install_gui run_gui: DIR:=$(GUI_EXE_DIR)
dist: DIR:=$(BUILD_DIR)
 
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

run: run_gui

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

# documentation
.PHONY: dvi docs
dvi: $(GENDOC_DIR)
	@doxygen $(DOXYFILE)
	@echo "project documentation can be found in $(GENDOC_DIR)"

docs: dvi
	@if [ "$(OS)" = "Linux" ]; then \
		xdg-open $(GENDOC_DIR)/index.html; \
	elif [ "$(OS)" = "Darwin" ]; then \
		open $(GENDOC_DIR)/index.html; \
	fi

# distribution
.PHONY: dist

dist: $(DIR) $(DIST_LIST)
	tar -czf $(DIR)/$(PROJECT_NAME)-$(VERSION).tar.gz $(DIST_LIST) 

# service
.PHONY: clean help

$(BUILD_DIR) $(GUI_EXE_DIR) $(TUI_EXE_DIR) $(TUI_SAVE_DIR) $(GUI_SAVE_DIR) $(GENDOC_DIR) $(GUI_CMAKE_DIR):
	@mkdir -p $@

$(DATA_FILE_FIRST) $(DATA_FILE_SECOND): $(SAVE_DIR)
	@touch $(SAVE_DIR)/$@

clean_tui: 
	@rm -fr $(TUI_EXE_DIR)

clean_gui:
	@rm -fr $(GUI_EXE_DIR)

clean_dvi:
	@rm -fr $(GENDOC_DIR)

clean:
	@rm -fr $(BUILD_DIR)

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
	test_first \n\
	test_second \n\
	gcov_report  \n\
	report  \n\
	style_make  \n\
	style_check  \n\
	cpp_check  \n\
	valgrind \n\
	clean \n\
	dvi \n\
	docs \n\
	dist \n\
	help \n\
	* Installation and distribution directories can  \n\
	be set by adding >DIR= pwd/game_folder< to any  \n\
	uninstallation command"





