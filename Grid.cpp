#include "Grid.h"
#include "Types.h"

Grid::Grid()
{
}

Grid::~Grid() 
{
    grids.clear();
}

void Grid::Init(int Lines, int Columns)
{
    for (int i = 0; i < Lines; i++)
    {
        for (int j = 0; j < Columns; j++)
        {
            Types::GridBox* newBox = new Types::GridBox(i, j, false, (Columns * i + j));
            grids.push_back(*newBox);
        }
    }
}