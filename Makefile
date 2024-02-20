CFILES := draw.c game.c init.c main.c

all: $(CFILES)
	gcc -Wall -o game $(CFILES) -lraylib

run: all
	./game