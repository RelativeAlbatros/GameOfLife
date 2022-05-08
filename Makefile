PREFIX := /usr/local

GameOfLife: src/main.cpp src/Cell.cpp src/World.cpp
	g++ -pedantic -Wall -Werror -std=c++11 -lncurses -o bin/$@ $?

run: GameOfLife 
	./bin/GameOfLife 

debug: src/main.cpp src/Cell.cpp src/World.cpp
	g++ -g -pedantic -Wall -Werror -std=c++11 -lncurses -o bin/$@ $?
	@echo finished debugging. checking code
	cppcheck --enable=all --inconclusive -v --suppress=missingIncludeSystem src/

install: GameOfLife 
	mv bin/GameOfLife ${PREFIX}/bin/ 

clean: 
	rm -f bin/GameOfLife 
