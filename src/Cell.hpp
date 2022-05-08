#pragma once

class Cell {
private:
    int state;
public:
    Cell();
    int GetState() const;
    void Die();
    void Revive();
};