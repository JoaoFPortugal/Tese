CC = gcc
CFLAGS = -lm -g -Wall
DEPS = labelingalg.h auxfunc.h
OBJ = driver.o labelingalg.o auxfunc.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

driver: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


clean:
	-rm driver *.o
