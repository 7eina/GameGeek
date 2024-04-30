
all: main

main: main.cc GameGeek.o Game.o Session.o Date.o
	g++ -o main main.cc GameGeek.o Game.o Session.o Date.o

GameGeek.o: GameGeek.cc GameGeek.h
	g++ -c GameGeek.cc

Game.o: Game.cc Game.h defs.h 
	g++ -c Game.cc 

Session.o: Session.cc Session.h 
	g++ -c Session.cc 

Date.o: Date.cc Date.h
	g++ -c Date.cc 

clean:
	rm -f test *.o