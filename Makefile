.DEFAULT_GOAL := debug

CC := gcc
CFLAGS := -Isrc/include/ -o nevec
FILES := src/main.c src/err/err.c src/err/render.c src/lexer/lexer.c \
src/lexer/token.c
LIBS := -lm

debug:
	@$(CC) $(CFLAGS) -g $(FILES) $(LIBS)
