hg clone http://hg.libsdl.org/SDL

CC = gcc
CFLAGS = -I. $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs)

ODIR = obj/
OBJ = $(ODIR)Widget.o $(ODIR)Batch.o $(ODIR)SDLRenderer.o $(ODIR)main.o
DEPS = Types.h

$(ODIR)%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cluce: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
