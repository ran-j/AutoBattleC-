#include "Grid.h"
#include "Types.h"


Grid::Grid(int Lines, int Columns)
{
    xLenght = Lines;
    yLength = Columns;
    //Console.WriteLine("The battle field has been created\n");
    for (int i = 0; i < Lines; i++)
    {

        for (int j = 0; j < Columns; j++)
        {
            Types::GridBox* newBox = new Types::GridBox(i, j, false, (Columns * i + j));
            grids.push_back(*newBox);
            //Console.Write($"{newBox.Index}\n");
        }
    }
	//drawBattlefield(Lines, Columns);
}

Grid::~Grid() 
{

}

//TODO remove this parameters
void Grid::drawBattlefield(int Lines, int Columns)
{
    #ifdef __linux__ 
        system("clear");
    #elif _WIN32
        system("cls");
    #endif       
    for (int i = 0; i < Lines; i++)
    {
        for (int j = 0; j < Columns; j++)
        {
            Types::GridBox* currentgrid = &grids[(Columns * i + j)];
            if (currentgrid->ocupied)
            {
                //TODO draw player different from enemy
                printf("[X]\t");
            }
            else
            {
                printf("[ ]\t");
            }
        }
        printf("\n");
    }
    printf("\n");
}