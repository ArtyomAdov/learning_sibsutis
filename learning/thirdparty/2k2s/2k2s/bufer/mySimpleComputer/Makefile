BIN_NAME = main

SRC_PATH = src
BUILD_PATH = build
BIN_PATH = bin
LIB_PATH = lib
# INCLUDE_PATH_FLAGS =
LIB_FLAG = -L

SRC_EXT = c

CC = gcc

COMPILE_FLAGS = -std=c99 -Wall -Werror -O0 -g

SOURCES = $(shell find $(SRC_PATH)/ -name '*.$(SRC_EXT)')

OBJECTS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)

LIB_SOURCES = $(filter-out $(SRC_PATH)/main.c, $(SOURCES))

LIBS = $(LIB_SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(LIB_PATH)/lib%.a)

LLIBS = $(filter-out -lhelper, $(LIBS:$(LIB_PATH)/lib%.a=-l%))

all: makedirs main
	
main: $(BUILD_PATH)/main.o $(LIBS)
	$(CC) $(COMPILE_FLAGS) $(LIB_FLAG)$(LIB_PATH) $(BUILD_PATH)/main.o -o $(BIN_PATH)/$(BIN_NAME) $(LLIBS)

$(BUILD_PATH)/main.o: $(SRC_PATH)/main.$(SRC_EXT)
	$(CC) $(COMPILE_FLAGS) $(INCLUDE_PATH_FLAGS) $< -c -o $@

$(LIB_PATH)/lib%.a : $(BUILD_PATH)/%.o
	ar rcs $@ $^

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	$(CC) $(COMPILE_FLAGS) $(INCLUDE_PATH_FLAGS) $< -c -o $@

makedirs:
	@mkdir $(BIN_PATH) -p
	@mkdir $(BUILD_PATH) -p
	@mkdir $(LIB_PATH) -p

.PHONY:

clean:
	$(shell printf '\043 Cleaned \043')
	@rm -rf $(BIN_PATH)
	@rm -rf $(BUILD_PATH)
	@rm -rf $(LIB_PATH)

run:
	@clear
	@bin/main

tog:
	@make clean
	@make
	@make run