#include <iostream> 
#include <unistd.h>
#include "World.hpp"
#include "Cell.hpp"
 
static void game(){
	static World theworld;
	theworld.ReviveCell(1,2);
	while (true) {
		theworld.Clear();
		theworld.Draw();
		sleep(1);
		theworld.Tick();
	}
}

int main(int argc, char *argv[]) { 
	game();
} 
