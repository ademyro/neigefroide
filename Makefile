.DEFAULT_GOAL := debug

SRC := src/

CC := gcc
CFLAGS := -Wall -Wextra -pedantic -Werror -Wconversion -Isrc/include/ -o nevec
FILES := $(shell find $(SRC) -name '*.c')
LIBS := -lm

debug:
	@$(CC) $(CFLAGS) -g $(FILES) $(LIBS)
