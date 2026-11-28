CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Werror
CPPFLAGS := -Iinclude -Isrc

SOURCES := $(wildcard src/*.c src/core/*.c src/modules/*/*.c src/utils/*.c src/storage/*.c)
HEADERS := $(wildcard include/*.h src/*/*.h src/*/*/*.h src/*/*/*/*.h)
TARGET := build/library_system

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES) -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)