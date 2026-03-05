CC = gcc
CFLAGS = -lm

SRC = ODE_solver/ODE_solver.c \
      ODE_solver/ODE_function.c \
      ray_cast/ray_cast.c

TARGET = output_executable

all:
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)