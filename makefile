all: exec

exec: main.o graphe.o pixel.o
	g++ -g -Wall graphe.o pixel.o main.o -o exec

main.o: main.cpp graphe.h pixel.h
	g++ -g -Wall -c main.cpp -o main.o

graphe.o: graphe.cpp graphe.h pixel.h
	g++ -g -Wall -c graphe.cpp -o graphe.o

pixel.o: pixel.cpp pixel.h
	g++ -g -Wall -c pixel.cpp -o pixel.o

clean :
	rm *.o exec