#pragma once
class Types
{
public:

    //TODO better names for this Struct
    struct GridBox
    {
        int xIndex;
        int yIndex;
        bool ocupied;
        int Index;

        GridBox(int x, int y, bool bOccupied, int index)
        {
            xIndex = x;
            yIndex = y;
            ocupied = bOccupied;
            Index = index;
        }
    };

    enum CharacterClass
    {
        Paladin = 1,
        Warrior = 2,
        Cleric = 3,
        Archer = 4
    };

};

