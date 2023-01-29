#pragma once
#include <Vector>
#include "Types.h"

class Grid
{

public:

    Grid();
    ~Grid();

    void Init(int Lines, int Columns);

private:
    std::vector<Types::GridBox> grids;
private:
    friend class Engine;
    friend class WorldMatrix;
};

