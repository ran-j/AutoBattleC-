#pragma once
#include <Vector>
#include "Types.h"

class Grid
{

public:

    Grid(int Lines, int Columns);
    ~Grid();

private:
    std::vector<Types::GridBox> grids;
private:
    friend class Engine;
};

