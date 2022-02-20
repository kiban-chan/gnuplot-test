COMPILER = gcc
CFLAGS = -Wall
LDFLAGS = -lm
BUILD_DIR = build

.PHONY: all clean

all: $(BUILD_DIR) $(BUILD_DIR)/main

$(BUILD_DIR)/main: $(BUILD_DIR)/main.o
	$(COMPILER) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/main.o: main.c
	$(COMPILER) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

clean: $(BUILD_DIR)
	rm build/*
