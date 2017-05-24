# ------------------------------------------------------------------------------------------------

PROJECT_ROOT = clog
SRCS = $(PROJECT_ROOT)/src
TESTS = $(PROJECT_ROOT)/tests

BUILD_DIR = ./_build

# ------------------------------------------------------------------------------------------------

CC=gcc

# ------------------------------------------------------------------------------------------------

test:
	$(CC) -o $(BUILD_DIR)/test_clog $(TESTS)/test_clog.c $(SRCS)/clog.c -I. $(SRCS)/clog.h
	$(BUILD_DIR)/test_clog

build:
	mkdir _build

clean:
	rm -r _build/*
