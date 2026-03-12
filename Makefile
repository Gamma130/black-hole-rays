CC = gcc
CFLAGS = -lm

SRC = ODE_solver/ODE_solver.c \
      ODE_solver/ODE_function.c \
      ray_engine/ray_cast.c \
	  ray_engine/ray_engine.c

TARGET = output_executable

all:
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)