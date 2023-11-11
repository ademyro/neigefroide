.DEFAULT_GOAL := debug

SRC := src/

CC := gcc
CFLAGS := -Wall -Wextra -pedantic -Werror -Wconversion -Isrc/include/ -o nevec
FILES := $(shell find $(SRC) -name '*.c')
LIBS := -lm

debug:
	@$(CC) $(CFLAGS) -g $(FILES) $(LIBS)

test:
	@for file in tests/*.nv; do \
		echo "Test $${file}"; \
		./nevec "$${file}"; \
	done	
