#pragma once

#include "Cell.hpp"

#include <ncurses.h>

#define WorldLimit 20


class World {
private:
    Cell world[WorldLimit][WorldLimit];
public:
    World();
    ~World();
    void ScreenInit() const;
    void Draw() const;
    void Clear() const;
    void ReviveCell(const int& x,const int& y);
    void KillCell(const int& x,const int& y);
    int CellState(const int& x,const int& y) const;
    int LivingNeighbours(const int& x,const int& y) const;
    // called every frame
    void Tick() ;
};
