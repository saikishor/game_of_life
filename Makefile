CC = gcc
CFLAGS = -Wall -I/usr/include/ -I.
LDFLAGS = -lncurses
DEPS = game.h
OBJ = code.o init.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

game: $(OBJ)
	gcc -o $@ $^ $(LDFLAGS) $(CFLAGS)

clean: 
	rm -f $(OBJ) game
