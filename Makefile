CC = gcc
CFLAGS = -std=c99 -Wall -lm -lSDL2

SRC = main.c \
	  ODE_solver/ODE_solver.c \
      ODE_solver/ODE_function.c \
      ray_engine/ray_cast.c \
      ray_engine/ray_engine.c \
	  display/display.c

TARGET = output_executable

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)