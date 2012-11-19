run: juego
	./juego

juego: main.o
	gcc main.o -o juego `pkg-config sdl --cflags --libs` -lSDL_mixer -lSDL_ttf -lSDL_image
main.o: main.c
	gcc -c main.c `pkg-config sdl --cflags` 

clean:
	rm juego main.o
