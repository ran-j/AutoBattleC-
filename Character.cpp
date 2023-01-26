#include "Grid.h"
#include "Character.h"
#include "Types.h"
#include "Character.h"
#include <vector>
#include <algorithm>

using namespace std;
Character::Character(Types::CharacterClass charcaterClass) : currentBox{-1, -1, false, -1}
{
}

Character::~Character()
{
}

bool Character::TakeDamage(float amount)
{
    if ((Health -= BaseDamage) <= 0)
    {
        Die();
        return true;
    }
    return false;
}

int Character::getIndex(std::vector<Types::GridBox *> v, int index)
{
    return 0;
}

void Character::Die()
{
    // TODO >> kill
    // TODO >> end the game?
}

void Character::WalkTo(bool CanWalk)
{
}

bool Character::StartTurn(Grid *battlefield)
{

    if (CheckCloseTargets(battlefield))
    {
        Attack(Character::target);

        return false;
    }
    else
    { // if there is no target close enough, calculates in wich direction this character should move to be closer to a possible target
        // TODO draw only once

        if (currentBox.xIndex > target->currentBox.xIndex)
        {
            if (std::find_if(battlefield->grids.begin(), battlefield->grids.end(), [&](const Types::GridBox &box)
                             { return box.Index == currentBox.Index; }) != battlefield->grids.end())

            {
                currentBox.ocupied = false;
                battlefield->grids[currentBox.Index] = currentBox;

                currentBox = (battlefield->grids[currentBox.Index - 1]);
                currentBox.ocupied = true;
                battlefield->grids[currentBox.Index] = currentBox;
                // Console.WriteLine($"Player {PlayerIndex} walked left\n");
    
                return true;
            }
        }
        else if (currentBox.xIndex < target->currentBox.xIndex)
        {
            currentBox.ocupied = false;
            battlefield->grids[currentBox.Index] = currentBox;
            currentBox = (battlefield->grids[currentBox.Index + 1]);
            battlefield->grids[currentBox.Index] = currentBox;
            // Console.WriteLine($"Player {PlayerIndex} walked right\n");
            return true;
        }

        if (currentBox.yIndex > target->currentBox.yIndex)
        {
            currentBox.ocupied = false;
            battlefield->grids[currentBox.Index] = currentBox;
            currentBox = battlefield->grids[(currentBox.Index - battlefield->xLenght)];
            currentBox.ocupied = true;
            battlefield->grids[currentBox.Index] = currentBox;
            // Console.WriteLine($"PlayerB {PlayerIndex} walked up\n");
            return true;
        }
        else if (currentBox.yIndex < target->currentBox.yIndex)
        {
            currentBox.ocupied = false;
            battlefield->grids[currentBox.Index] = currentBox;
            currentBox = battlefield->grids[currentBox.Index + battlefield->xLenght];
            currentBox.ocupied = true;
            battlefield->grids[currentBox.Index] = currentBox;
            // Console.WriteLine($"Player {PlayerIndex} walked down\n");

            return true;
        }
    }
    return false;
}

bool Character::CheckCloseTargets(Grid *battlefield)
{
    // TODO handle this
    return false;
}

void Character::Attack(std::shared_ptr<Character> target)
{
    // TODO handle this
}
