# Makefile for libtiny3d demos and tests

CC = gcc
CFLAGS = -Wall -Wextra -O2

# Include directories
INCLUDES = -Iinclude -Isrc

# Source files for each target
LIGHTING_SRCS = demo/main_lighting.c src/renderer.c src/canvas.c src/math3d.c src/lighting.c src/animation.c demo/generate_soccer.c
SOCCER_SRCS = demo/main_soccer.c demo/generate_soccer.c src/renderer.c src/math3d.c src/canvas.c
CUBE_SRCS = tests/test_math.c src/math3d.c src/canvas.c

# Output binaries
LIGHTING_BIN = light_anima
SOCCER_BIN = soccer_combo
CUBE_BIN = test_math.exe

# Default target: build all
all: $(LIGHTING_BIN) $(SOCCER_BIN) $(CUBE_BIN)

$(LIGHTING_BIN): $(LIGHTING_SRCS)
	$(CC) -Iinclude $(LIGHTING_SRCS) -lm -o $(LIGHTING_BIN)

$(SOCCER_BIN): $(SOCCER_SRCS)
	$(CC) -Iinclude $(SOCCER_SRCS) -lm -o $(SOCCER_BIN)

$(CUBE_BIN): $(CUBE_SRCS)
	$(CC) $(INCLUDES) $(CUBE_SRCS) -o $(CUBE_BIN) -lm

clean:
	rm -f $(LIGHTING_BIN) $(SOCCER_BIN) $(CUBE_BIN)

.PHONY: all clean
