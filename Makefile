CC = gcc
CINC = -Iinclude
CFLAGS = -g -lJakestering

INC_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
BUILD_DIR = build

.PHONY: all
all: $(BIN_DIR)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $< -c $(CFLAGS) $(CINC) -o $@

$(BIN_DIR): always $(OBJ_DIR)/main.o 
	mkdir -p $(BIN_DIR)
	$(CC) $(OBJ_DIR)/main.o $(CFLAGS) $(CINC) -o $@/logAnal


.PHONY: clean
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR) $(BUILD_DIR)
	clear

.PHONY: always
always:
	mkdir -p $(OBJ_DIR)

