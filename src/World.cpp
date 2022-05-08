#include "World.hpp"

#include <exception>
#include <iostream>
#include <unistd.h>
#include <ncurses.h>

#define ALIVE_CELL "@"
#define DEAD_CELL "."

World::World() {
    for(int i=0; i<WorldLimit; ++i) {
        for(int j=0; j<WorldLimit; ++j) {
            KillCell(i, j);
        }
    }
}

World::~World() {
    endwin();
}

void World::ScreenInit() const {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
}

void World::Draw() const {
    for(int i=0; i<WorldLimit; ++i) {
        for(int j=0; j<WorldLimit; ++j) {
            if (CellState(i, j) == 1)
                std::cout << ALIVE_CELL;
            else
                std::cout << DEAD_CELL;
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void World::ReviveCell(const int& x, const int& y) {
    world[x][y].Revive();
}

void World::KillCell(const int& x, const int& y) {
    world[x][y].Die();
}

void World::Clear() const {
    std::cout << std::flush;
    #ifdef __WIN32__
        system("CLS");
    #elif __unix__
        system("clear");
    #endif
};

int World::CellState(const int& x, const int& y) const {
    if (x < 0 || x > WorldLimit)
        throw std::invalid_argument("x-value out of range");
    if (y < 0 || y > WorldLimit)
        throw std::invalid_argument("y-value out of range");
    return world[y][x].GetState();
}

int World::LivingNeighbours(const int& x, const int& y) const {
    int neighbours = 0;
    // at the edge of the world
    if ((x == 0 || x == WorldLimit-1) && (y == 0 || y == WorldLimit-1)) {
        int i = x+1;
        for(int j=y; j<=y+1; ++j) {
            if (CellState(i, j) == 1)
                ++neighbours;
        }
    } 
    // at the upper and lower borders
    else if (y == 0 || y == WorldLimit-1) { 
        for(int i=x-1; i<=x+1; ++i) {
            for(int j=y; j<=y+1; ++j) {
                if (CellState(i, j) == 1)
                    ++neighbours;
            }
        }
    } 
    // at the right and left borders
    else if  (x == 0 || x == WorldLimit-1) {
        for(int i=x; i<=x+1; ++i) {
            for(int j=y-1; j<=y+1; ++j) {
                if (CellState(i, j) == 1)
                    ++neighbours;
            }
        }
    } else {
        for(int i=x-1; i<=x+1; ++i) {
            for(int j=y-1; j<=y+1; ++j) {
                try {
                    if (CellState(i, j) == 1)
                        ++neighbours;
                } catch (std::exception &e) {
                    std::cerr << e.what() << "\n";
                    std::cerr << "x: "<< i << " j: "<< y << "\n";
                    continue;
                }
            }
        }
    }
    if (neighbours != 0)
        std::cout << neighbours << "has (" << x << y << ")\n";
    return neighbours;
}

void World::Tick() {
    int neighbours;
    for(int i=0; i<WorldLimit; ++i) {
        for(int j=0; j<WorldLimit; ++j) {
            try {
                neighbours = LivingNeighbours(i, j);
                if (CellState(i, j) == 1) {
                    if (neighbours == 2 || neighbours == 3)
                        continue;
                } else if (CellState(i, j) == 0 && neighbours == 3){
                    ReviveCell(i, j);
                } else {
                    KillCell(i, j);
                }
            } catch (std::exception &e) {
                std::cerr << e.what() << "\n";
                std::cerr << "skipping cell(" << i << "," << j << ")\n";
                continue;
            }
        }
    }
}
