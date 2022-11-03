CC = gcc

CFLAGS = -Wall -Wextra -pedantic -ansi -g
LDFLAGS = $(CFLAGS)

BUILD_DIR = build
BIN = loader.exe

all: clean $(BUILD_DIR) $(BUILD_DIR)/$(BIN)

$(BUILD_DIR)/$(BIN): $(BUILD_DIR)/vector.o $(BUILD_DIR)/person.o $(BUILD_DIR)/loader.o
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/vector.o: src/vector.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/person.o: src/person.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/loader.o: src/loader.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR):
	mkdir $@

# on linux use rm -rf $(BUILD_DIR)
clean:
	del /F /Q $(BUILD_DIR)  
