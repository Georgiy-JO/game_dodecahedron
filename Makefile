# ----------------------------------------------------------------------
# Main Makefile for the Game Dodecahedron
# ----------------------------------------------------------------------
#
# Purpose:
#   This Makefile automates the build, clean, install, uninstall, 
#	distribute, document generration, unit tests and check processes 
#	for the Game Dodecahedron application. It is a cut copy of the 
#	Makefile from the src folder (for more options check thst one out).
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
#   gcov_report			- Create a html report of the executed tests.
#   report				- Create a html report of the executed tests and open 
#						it in the default browser.
#   clean    			- Removes all build artifacts and created files.
#   valgrind			- run all tests with valgrind and write the results to a file.
#   style_check    		- Runs a style check of all code files.
# 	style_make			- Change all code files so they passe style checks (Google st.).
# 	cpp_check			- Check all code files with CppCheck tool.
#	dvi					- Create a html code documentation.
#	docs				- Create a html code documentation and open 
#						it in the default browser.
#	dist				- Create an archive for distribution.
#						Distribution directory can be set by adding
#						"DIR=pwd/location" to the command.
#	help 				- List of targets.
#
#
# Usage:
#   make target
# ----------------------------------------------------------------------

MAKE = make --no-print-directory
MAKE_REMOTE = cd $(SRC_DIR) && make --no-print-directory

# directories 
ROOT_DIR = .
SRC_DIR=$(ROOT_DIR)/src

# ----------------------------------------------------------------------
# targets
.PHONY: all install uninstall clean dvi dist test
.PHONY: install_tui_first install_tui_second run_tui uninstall_tui
.PHONY: install_gui_first install_gui_second gun_tui uninstall_gui
.PHONY: run gcov_report report docs help
.PHONY: valgrind style_check style_make cpp_check

# all
all: 
	@$(MAKE_REMOTE) all

# test and report
test:
	@$(MAKE_REMOTE) test

gcov_report:
	@$(MAKE_REMOTE) gcov_report

report:
	@$(MAKE_REMOTE) report

# tui part
install_tui_first:
	@$(MAKE_REMOTE) install_tui_first

install_tui_second:
	@$(MAKE_REMOTE) install_tui_second

uninstall_tui: 
	@$(MAKE_REMOTE) uninstall_tui

run_tui: 
	@$(MAKE_REMOTE) run_tui

# gui part
install_gui_first:
	@$(MAKE_REMOTE) install_gui_first

install_gui_second:
	@$(MAKE_REMOTE) install_gui_second

uninstall_gui: 
	@$(MAKE_REMOTE) uninstall_gui

run_gui: 
	@$(MAKE_REMOTE) run_gui

# main part
install: 
	@$(MAKE_REMOTE) install

run: 
	@$(MAKE_REMOTE) run

uninstall: 	
	@$(MAKE_REMOTE) uninstall

# check part
style_make:
	@$(MAKE_REMOTE)  style_make

style_check: 
	@$(MAKE_REMOTE) style_check

cpp_check: 
	@$(MAKE_REMOTE) cpp_check

valgrind:
	@$(MAKE_REMOTE) valgrind

# documentation
dvi:
	@$(MAKE_REMOTE) dvi

docs:
	@$(MAKE_REMOTE) docs

# distribution
dist:	
	@$(MAKE_REMOTE) dist

# service
clean:
	@$(MAKE_REMOTE) clean

help target:
	@echo "Main targets are: \n\
	all \n\
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
	gcov_report  \n\
	report  \n\
	style_make  \n\
	style_check  \n\
	cpp_check  \n\
	valgrind \n\
	clean  \n\
	dvi \n\
	docs \n\
	dist \n\
	help \n\
	* Installation and distribution directories can  \n\
	be set by adding >DIR= pwd/game_folder< to any  \n\
	uninstallation command"  	
