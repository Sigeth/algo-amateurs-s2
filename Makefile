main: main.o libisentlib.a
	gcc -Wall main.o -o main libisentlib.a -lm -lglut -lGL -lX11

main.o: main.c GfxLib/GfxLib.h GfxLib/BmpLib.h GfxLib/ESLib.h
	gcc -Wall -c main.c

libisentlib.a: BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o SocketLib.o ThreadLib.o TortueLib.o VectorLib.o WavLib.o
	ar r libisentlib.a BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o SocketLib.o ThreadLib.o TortueLib.o VectorLib.o WavLib.o
	ranlib libisentlib.a

BmpLib.o: GfxLib/BmpLib.c GfxLib/BmpLib.h GfxLib/OutilsLib.h
	gcc -Wall -O2 -c GfxLib/BmpLib.c

ESLib.o: GfxLib/ESLib.c GfxLib/ESLib.h GfxLib/ErreurLib.h
	gcc -Wall -O2 -c GfxLib/ESLib.c

ErreurLib.o: GfxLib/ErreurLib.c GfxLib/ErreurLib.h
	gcc -Wall -O2 -c GfxLib/ErreurLib.c

GfxLib.o: GfxLib/GfxLib.c GfxLib/GfxLib.h GfxLib/ESLib.h
	gcc -Wall -O2 -c GfxLib/GfxLib.c -I/usr/include/GL

OutilsLib.o: GfxLib/OutilsLib.c GfxLib/OutilsLib.h
	gcc -Wall -O2 -c GfxLib/OutilsLib.c

SocketLib.o: GfxLib/SocketLib.c GfxLib/SocketLib.h
	gcc -Wall -O2 -c GfxLib/SocketLib.c

ThreadLib.o: GfxLib/ThreadLib.c GfxLib/ThreadLib.h
	gcc -Wall -O2 -c GfxLib/ThreadLib.c

TortueLib.o: GfxLib/TortueLib.c GfxLib/TortueLib.h GfxLib/GfxLib.h
	gcc -Wall -O2 -c GfxLib/TortueLib.c

VectorLib.o: GfxLib/VectorLib.c GfxLib/VectorLib.h
	gcc -Wall -O2 -c GfxLib/VectorLib.c -msse3

WavLib.o: GfxLib/WavLib.c GfxLib/WavLib.h GfxLib/OutilsLib.h
	gcc -Wall -O2 -c GfxLib/WavLib.c -Wno-unused-result
clean:
	rm -f *~ *.o