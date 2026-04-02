CC = gcc
CFLAGS = -std=c99 -Wall
LIBS = -lm -lSDL2 -lSDL2_image

SRC = \
	ODE_solver/ODE_solver.c \
	ODE_solver/ODE_function.c \
	ray_engine/ray_cast.c \
	ray_engine/ray_engine.c \
	display/display.c

MAIN = main.c
TEST = tests/test_ray_engine.c

TARGET = output_executable
TEST_TARGET = test_executable

all:
	$(CC) $(CFLAGS) $(MAIN) $(SRC) -o $(TARGET) $(LIBS)

run: all
	./$(TARGET)

test:
	$(CC) $(CFLAGS) $(TEST) $(SRC) -o $(TEST_TARGET) $(LIBS)
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET)