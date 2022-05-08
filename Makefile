PREFIX := /usr/local

GameOfLife: src/main.cpp src/Cell.cpp src/World.cpp
	g++ -pedantic -Wall -Werror -std=c++11 -lncurses -o bin/$@ $?

run: GameOfLife 
	./bin/GameOfLife 

install: GameOfLife 
	mv bin/GameOfLife ${PREFIX}/bin/ 

clean: 
	rm -f bin/GameOfLife 
