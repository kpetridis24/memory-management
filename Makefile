CC=gcc
CFLAGS=-O3
BUILD_DIR=build
SRC_DIR=src
INCLUDE_DIR=./include
SOURCES := $(shell find $(SRC_DIR) -name '*.c')

$(info $(shell mkdir -p $(BUILD_DIR)))

static:
	$(CC) -o $(BUILD_DIR)/main -I$(INCLUDE_DIR) $(SOURCES) $(CFLAGS)
	./build/main 0

dynamic:
	$(CC) -o $(BUILD_DIR)/main -I$(INCLUDE_DIR) $(SOURCES) $(CFLAGS)
	./build/main 1
