OS=$(shell uname)
CC = gcc

# Flags
MAIN_FLAGS = -std=c11
DEBUG_FLAGS = -Wall -Wextra -Werror
VALG_FLAGS = -g
POSIX_FLAG = -D_POSIX_C_SOURCE=201706L
COVLAGS =-fprofile-arcs -ftest-coverage
CHLIB = -lcheck
MATHLIB = -lm
LIBFLAGS= $(CHLIB) $(MATHLIB)
ifeq ($(OS), Linux)
	CHLIB += -lsubunit
endif

# Checkers
VALG = valgrind --tool=memcheck  --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=$(VALG_FILE) ./
CPPCHECK = cppcheck --enable=all --suppress=missingIncludeSystem  --force --check-level=exhaustive --checkers-report=$(CPPCHECK_FILE) 
CLANG = clang-format --style=Google

# directories 
BUILD_DIR = build
SRC_DIR=src
TEST_DIR=tests
OBJ_DIR = $(BUILD_DIR)/service_files
COV_DIR = $(BUILD_DIR)/coverage
VALG_FILE = $(BUILD_DIR)/RESULT_VALGRIND.txt
CPPCHECK_FILE = $(BUILD_DIR)/RESULT_CPPCHECK.txt

# main files 
# SRC_FILES = $(shell find . ! -path './tests/*' -type  f -name '*.c')			# for dif file conf
SRC_FILES = $(shell find $(SRC_DIR)/ -type  f -name '*.c')
HEAD_FILES = $(shell find $(SRC_DIR)/ -type f -name '*.h')
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:.c=.o)))

# test files
TEST_SRC_FILES = $(shell find $(TEST_DIR)/ -type f -name '*.c')
TEST_OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(TEST_SRC_FILES:.c=.o)))
TEST_EXEC = $(addprefix $(BUILD_DIR)/, $(notdir $(TEST_SRC_FILES:.c=)))
TEST_COV_OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(TEST_SRC_FILES:.c=.cov.o)))
TEST_COV_EXEC = $(addprefix $(BUILD_DIR)/, $(notdir $(TEST_SRC_FILES:.c=_cov)))

# lib files		(unique for a project)
PROJECT_NAME= ..........
MAIN_HEADER=$(SRC_DIR)/$(PROJECT_NAME:=.h)
LIB_NAME=$(PROJECT_NAME:=.a)
LIB_COV_NAME=$(PROJECT_NAME:=.cov.a)
LIB_LOC=$(BUILD_DIR)/$(LIB_NAME)

# target specific variables
$(LIB_NAME): MAIN_FLAGS:= $(MAIN_FLAGS) $(DEBUG_FLAGS) $(POSIX_FLAG) #$(VALG_FLAGS)
$(TEST_EXEC): MAIN_FLAGS:= $(MAIN_FLAGS) $(DEBUG_FLAGS) $(POSIX_FLAG) #$(VALG_FLAGS)
$(LIB_COV_NAME): MAIN_FLAGS:=  $(MAIN_FLAGS) $(DEBUG_FLAGS) $(POSIX_FLAG) $(COVLAGS)
$(TEST_COV_EXEC): MAIN_FLAGS:= $(MAIN_FLAGS) $(DEBUG_FLAGS) $(POSIX_FLAG) $(COVLAGS)


# targets
all: $(LIB_NAME)

# library
$(LIB_NAME): clear_o $(OBJ_DIR) $(OBJ_FILES)
	ar rcs $@ $(OBJ_FILES)
	@mv $(LIB_NAME) $(LIB_LOC)    

$(LIB_COV_NAME): clear_o $(OBJ_DIR) $(OBJ_FILES)
	ar rcs $@ $(OBJ_FILES)            

# tests
$(TEST_EXEC): clear_o $(LIB_NAME) $(TEST_OBJ_FILES)
	$(CC) $(MAIN_FLAGS) $(TEST_OBJ_FILES) -o $@ $(LIB_LOC) $(LIBFLAGS)
	make -s clear_o

test: $(TEST_EXEC)
	@./$(TEST_EXEC)


$(TEST_COV_EXEC): clear_o $(LIB_COV_NAME) $(TEST_OBJ_FILES)
	$(CC) $(MAIN_FLAGS) $(TEST_OBJ_FILES) -o $@ $(LIB_COV_NAME) $(LIBFLAGS)
	rm -fr $(LIB_COV_NAME)

test_cov: $(TEST_COV_EXEC)
	@./$(TEST_COV_EXEC)


# object files
$(OBJ_DIR)/%.o: %.c
	@$(CC) $(MAIN_FLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: */%.c
	@$(CC) $(MAIN_FLAGS) -c $< -o $@


# coverage & report
coverage: test_cov
	gcov -b --object-directory=$(OBJ_DIR) $(SRC_FILES)  

gcov_report: $(COV_DIR) coverage
	gcovr  --object-directory $(OBJ_DIR)  -r . --html --html-details --output=$(COV_DIR)/    
	@make -s clear_gc
	@make -s clear_o


# deployment
dep_lib: $(LIB_NAME)
	@cp $(MAIN_HEADER) $(BUILD_DIR)/$(notdir $(MAIN_HEADER))


#checkers 
clang_all:
	$(CLANG) -i $(HEAD_FILES) $(SRC_FILES) $(TEST_SRC_FILES) $(MAIN_HEADER)

clang_check:
	@$(CLANG) -n $(HEAD_FILES) $(SRC_FILES) $(TEST_SRC_FILES) $(MAIN_HEADER)
	$(CLANG) -n $(shell find . -type f -name '*.c' -o -name '*.h')

valgrind_me: $(TEST_EXEC)
	$(VALG)$(TEST_EXEC)

cpp_check:
	$(CPPCHECK) $(shell find $(TEST_DIR) $(SRC_DIR) -type f \( -name '*.c' -o -name '*.h' \))


# service
$(OBJ_DIR) $(BUILD_DIR) $(COV_DIR):
	@mkdir -p $@

clear_o: 
	@rm -fr $(OBJ_DIR)

clear_gc:
	@rm -fr $(OBJ_DIR)/*.gc*	
	@rm -fr *.gc*

clear_cov:
	@rm -fr $(COV_DIR)

clear: clear_cov clear_gc clear_o
	rm -fr $(BUILD_DIR) $(LIB_NAME) $(LIB_COV_NAME) $(VALG_FILE)  $(CPPCHECK_FILE)  

clean: clear

rebuild_test: clear test

rebuild_test_cov: clear test_cov

rebuild_report: clear gcov_report



.PHONY: test $(LIB_NAME) gcov_report clean all 