apc.exe: apc.o add.o mul.o sub.o div.o
	gcc -o apc.exe apc.o add.o mul.o sub.o div.o
apc.o: apc.c
	gcc -c apc.c
add.o: add.c
	gcc -c add.c
mul.o: mul.c
	gcc -c mul.c
sub.o: sub.c
	gcc -c sub.c
div.o: div.c
	gcc -c div.c
clean:
	rm *.exe *.o