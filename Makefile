# ----------------------------------------------------------------------
# Main Makefile for the Game Dodecahedron
# ----------------------------------------------------------------------
#
# Purpose:
#   This Makefile automates the build, clean, install, uninstall, 
#	distribute, document generration, unit tests and check processes 
#	for the Game Dodecahedron application. It is a cut copy of the 
#	Makefile from the src folder (for more options check it out).
#
# Notes:
#	Currrent version icludeds games: tetris, snake.
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
#	intrall_tui 	- Install TUI version in the default location 
#						(/build). Installation directory can be set by
#						adding "DIR=pwd/location" to the command).
#	run_tui 		- Run the TUI version (will work only if it is installed).
#	uninstall_tui	- Uninstall TUI version.
#	test			- Build and run all libraries tests.
#   gcov_report		- Create a html report of the executed tests.
#   report			- Create a html report of the executed tests and open it in the default browser.
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

MAKE = make --no-print-directory
MAKE_REMOTE = cd $(SRC_DIR) && make --no-print-directory

# directories 
ROOT_DIR = .
SRC_DIR=$(ROOT_DIR)/src

# ----------------------------------------------------------------------
# targets
.PHONY: all test gcov_report report intrall_tui run_tui uninstall_tui install 
.PHONY: run uninstall style_make style_check cpp_check valgrind clean help

# all
all: install run 

# test and report
test:
	@$(MAKE_REMOTE) test

gcov_report:
	@$(MAKE_REMOTE) gcov_report

report:
	@$(MAKE_REMOTE) report

# tui part
install_tui:
	@$(MAKE_REMOTE) install_tui

uninstall_tui: 
	@$(MAKE_REMOTE) uninstall_tui

run_tui: 
	@$(MAKE_REMOTE) run_tui

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

# service
clean:
	@$(MAKE_REMOTE) clean

help target:
	@echo "Main targets are: \n\
	all  \n\
	install \n\
	run \n\
	uninstall \n\
	intrall_tui \n\
	run_tui \n\
	uninstall_tui \n\
	test \n\
	gcov_report  \n\
	report  \n\
	style_make  \n\
	style_check  \n\
	cpp_check  \n\
	valgrind \n\
	clean  \n\
	help"	
