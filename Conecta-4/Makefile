run: a.out
	./a.out
a.out: main.o conecta.o
	gcc main.o conecta.o
main.o: main.c
		gcc main.c -c
conecta.o: conecta.c
	gcc conecta.c -c
clear:
	rm -f *.o a.out
