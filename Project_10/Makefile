all: cp++.o
	gcc cp++.o -o cp -Wall -lm -lpthread

cp++.o:
	gcc -c cp++.c

clean:
	rm -rf *.o

run:
	./cp