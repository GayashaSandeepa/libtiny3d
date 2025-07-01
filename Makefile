CC=gcc
CFLAGS=-Iinclude -lm

SRC=src/canvas.c tests/demo/main.c
OUT=demo_task1
all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)
