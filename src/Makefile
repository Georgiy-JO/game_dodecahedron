# ----------------------------------------------------------------------
# Makefile for MyProject
# ----------------------------------------------------------------------
#
# Purpose:
#   This Makefile automates the build, clean, and testing processes
#   for the MyProject application. It compiles source code, links
#   libraries, and generates the final executable.
#
# Key Targets:
#   all      - Builds the project (default target).
#   clean    - Removes all build artifacts (e.g., object files, binaries).
#   test     - Runs the test suite to ensure code correctness.
#
# Usage:
#   To build the project:       make
#   To clean the build:         make clean
#   To run tests:               make test
#
# Notes:
#   - Requires GNU Make version 4.0 or later.
#   - Ensure all dependencies are installed before building.
#   - See the README.md for more details about the project.
#
# ----------------------------------------------------------------------



# main info
PROJECT_NAME=game_dodecahedron
VERSION =0.1

OS=$(shell uname)=
MAKE = make --no-print-directory

# Compillers
C = gcc
CC = g++

# Flags
MAIN_FLAGS_C = -std=c11
MAIN_FLAGS_CC = -std=c++17

DEBUG_FLAGS = -Wall -Wextra -Werror
POSIX_FLAG = -D_POSIX_C_SOURCE=201706L

VALG_FLAGS = -g
COV_FLAGS =-fprofile-arcs -ftest-coverage

CHLIB = -lcheck
MATHLIB = -lm
GTEST_FLAGS = -L/usr/lib/ -lgtest -lgtest_main -pthread #-Wl,--no-warn-search-mismatch

NCURLIB = -lncurses

LIBFLAGS= 
ifeq ($(OS), Linux)
	LIBFLAGS += -lsubunit
endif

# Checkers
VALG = valgrind --tool=memcheck  --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=$(VALG_FILE) ./
CPPCHECK = cppcheck --enable=all --suppress=missingIncludeSystem  --force --check-level=exhaustive --checkers-report=$(CPPCHECK_FILE) 
CLANG = clang-format --style=Google

# directories 
BUILD_DIR = ../build
TETRIS_DIR=brick_game/tetris
TEST_DIR=../tests
OBJ_DIR = $(BUILD_DIR)/service_files
COV_DIR = $(BUILD_DIR)/coverage
VALG_FILE = $(BUILD_DIR)/RESULT_VALGRIND.txt
CPPCHECK_FILE = $(BUILD_DIR)/RESULT_CPPCHECK.txt
GAME_DIR = $(BUILD_DIR)/Game
GENDOC_DIR = ../materials/gen_docs
DIST_DIR = $(BUILD_DIR)/distribution
CUI_DIR = gui/cli
GUI_DIR = gui/desktop