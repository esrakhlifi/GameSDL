prog: enigme.o main.o
	gcc  enigme.o main.o -o prog -g -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
main.o: main.c
	gcc -c main.c -g -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
enigme.o: enigme.c
	gcc -c enigme.c -g -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
