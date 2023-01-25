#include "Grid.h"
#include "Character.h"
#include "Types.h"
#include "Character.h"
#include <vector>
#include <algorithm>

using namespace std;
Character::Character(Types::CharacterClass charcaterClass): currentBox{-1,-1,true, -1}
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

int Character::getIndex(std::vector<Types::GridBox*> v, int index)
{
    return 0;
}

void Character::Die() 
{
	// TODO >> kill
	//TODO >> end the game?
}

void Character::WalkTo(bool CanWalk) 
{

}


void Character::StartTurn(Grid* battlefield) {

    {

        if (CheckCloseTargets(battlefield))
        {
            Attack(Character::target);


            return;
        }
        else
        {   // if there is no target close enough, calculates in wich direction this character should move to be closer to a possible target
            
            
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
                    //Console.WriteLine($"Player {PlayerIndex} walked left\n");
                    battlefield->drawBattlefield(5, 5);

                    return;
                }
            }
            else if (currentBox.xIndex < target->currentBox.xIndex)
            {
                currentBox.ocupied = false;
                battlefield->grids[currentBox.Index] = currentBox;
                currentBox = (battlefield->grids[currentBox.Index + 1]);
                return;
                battlefield->grids[currentBox.Index] = currentBox;
                //Console.WriteLine($"Player {PlayerIndex} walked right\n");
                battlefield->drawBattlefield(5, 5);
            }

            if (currentBox.yIndex > target->currentBox.yIndex)
            {
                battlefield->drawBattlefield(5, 5);
                currentBox.ocupied = false;
                battlefield->grids[currentBox.Index] = currentBox;
                currentBox = battlefield->grids[(currentBox.Index - battlefield->xLenght)];
                currentBox.ocupied = true;
                battlefield->grids[currentBox.Index] = currentBox;
                //Console.WriteLine($"PlayerB {PlayerIndex} walked up\n");
                return;
            }
            else if (currentBox.yIndex < target->currentBox.yIndex)
            {
                currentBox.ocupied = true;
                battlefield->grids[currentBox.Index] = currentBox;
                currentBox = battlefield->grids[currentBox.Index + battlefield->xLenght];
                currentBox.ocupied = false;
                battlefield->grids[currentBox.Index] = currentBox;
                //Console.WriteLine($"Player {PlayerIndex} walked down\n");
                battlefield->drawBattlefield(5, 5);

                return;
            }
        }
    }
}

bool Character::CheckCloseTargets(Grid* battlefield)
{
    return false;
}

void Character::Attack(std::shared_ptr<Character> target) 
{

}

