#pragma once
class Types
{
public:

    struct GridBox
    {
        int xIndex;
        int yIndex;
        bool ocupied;
        int Index;

        GridBox(int x, int y, bool ocupied, int index)
        {
            xIndex = x;
            yIndex = y;
            ocupied = ocupied;
            Index = index;
        }

        // bool operator== (const GridBox& another_grid) {
        //     return xIndex == another_grid.xIndex &&yIndex == another_grid.yIndex &&ocupied == another_grid.ocupied &&Index == another_grid.Index;
        // }

        // bool operator!= (const GridBox& another_grid) {
        //     return xIndex != another_grid.xIndex &&yIndex != another_grid.yIndex &&ocupied != another_grid.ocupied &&Index != another_grid.Index;
        // }
    };

    enum CharacterClass
    {
        Paladin = 1,
        Warrior = 2,
        Cleric = 3,
        Archer = 4
    };

};

