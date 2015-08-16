CC = gcc
CFLAGS = -I. -I/usr/include/lua5.2 $(shell sdl2-config --cflags) -Wall -Wextra -O2
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_image -llua5.2

ODIR = obj/
OBJ = $(ODIR)Widget.o $(ODIR)Batch.o $(ODIR)SDLApplication.o $(ODIR)FramesList.o $(ODIR)Cache.o $(ODIR)LuaBindings.o 
#OBJ = $(ODIR)Widget.o $(ODIR)Batch.o $(ODIR)SDLApplication.o $(ODIR)main.o $(ODIR)FramesList.o $(ODIR)Cache.o
DEPS = Types.h DynamicArray.h Widget.h Batch.h FramesList.h Cache.h SDLApplication.h

$(ODIR)%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cluce: $(OBJ) $(ODIR)main.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

#cluce.so: $(OBJ)
#	$(CC) -shared -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean: 
	rm obj/*
