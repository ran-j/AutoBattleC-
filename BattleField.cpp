#include "BattleField.h"

#include "Grid.h"
#include "BattleField.h"
#include "Types.h"
#include "Character.h"

#include <iostream>
#include <list>
#include <string>
#include <cstdlib>

using namespace std;

BattleField::BattleField() {
    
    grid = new Grid(5, 5);
    AllPlayers = list<shared_ptr<Character>>();
    int currentTurn = 0;
    int numberOfPossibleTiles = grid->grids.size();
    Setup();
}

void BattleField::Setup()
{
    GetPlayerChoice(); 
}

void BattleField::GetPlayerChoice()
{
    //asks for the player to choose between for possible classes via console.
    printf("Choose Between One of this Classes:\n");

    printf("[1] Paladin, [2] Warrior, [3] Cleric, [4] Archer");
    //store the player choice in a variable 
    
    int classIndex = 0;
    cin >> classIndex; 
    
    switch (classIndex)
    {
    case 1:
    case 2:
    case 3:
    case 4:
        CreatePlayerCharacter(classIndex);
        break;
    default:
        GetPlayerChoice();
        break;
    }
}

void BattleField::CreatePlayerCharacter(int classIndex)
{

    Types::CharacterClass characterClass = (Types::CharacterClass)classIndex;
    printf("Player Class Choice: {characterClass}");
    
    PlayerCharacter = std::make_shared<Character>(characterClass);
    
    PlayerCharacter->Health = 100;
    PlayerCharacter->BaseDamage = 20;
    PlayerCharacter->PlayerIndex = 0;

    CreateEnemyCharacter();

}

void BattleField::CreateEnemyCharacter()
{
    //randomly choose the enemy class and set up vital variables
    
    int randomInteger = GetRandomInt(1, 4);
    Types::CharacterClass enemyClass = (Types::CharacterClass)randomInteger;
    printf("Enemy Class Choice: {enemyClass}");
    printf("\n");

    EnemyCharacter = std::make_shared<Character>(enemyClass); 

    EnemyCharacter->Health = 100;

    PlayerCharacter->BaseDamage = 20;
    PlayerCharacter->PlayerIndex = 1;
    StartGame();

}

void BattleField::StartGame()
{
    //populates the character variables and targets
    EnemyCharacter->target = PlayerCharacter;
    PlayerCharacter->target = EnemyCharacter;

    AllPlayers.push_back(PlayerCharacter);
    AllPlayers.push_back(EnemyCharacter);

    AlocatePlayers();
    StartTurn();

}

void BattleField::StartTurn() {

    if (currentTurn == 0)
    {
        //AllPlayers.Sort();  
    }
    
    bool shouldReDraw = false;
    for (auto it = AllPlayers.begin(); it != AllPlayers.end(); ++it) {
       bool haveMoved = (*it)->StartTurn(grid);
       if(haveMoved)
       {
        shouldReDraw = true;        
       }
    }

    if (shouldReDraw)
    {
        grid->drawBattlefield(5, 5);
    }

    currentTurn++;
    HandleTurn();
}

void BattleField::HandleTurn()
{
    if (PlayerCharacter->Health == 0)
    {
        return;
    }
    else if (EnemyCharacter->Health == 0)
    {
        printf("\n");

        // endgame?

        printf("\n");

        return;
    }
    else
    {
        printf("\n");
        printf("Click on any key to start the next turn...\n");
        printf("\n");

        #ifdef __linux__ 
            system("read");
        #elif _WIN32
            system("pause");
        #endif       

        printf("\n");

        StartTurn();
    }
}

int BattleField::GetRandomInt(int min, int max)
{
    int range = max - min + 1;
    return rand() % range + min;
}

void BattleField::AlocatePlayers()
{
    AlocatePlayerCharacter();

}

void BattleField::AlocatePlayerCharacter()
{
    int random = GetRandomInt(0, grid->grids.size());
    auto l_front = grid->grids.begin();

    advance(l_front, random);

    if (!l_front->ocupied)
    {
        PlayerCurrentLocation = &*l_front;
        l_front->ocupied = true;
        PlayerCharacter->currentBox = *l_front;
        AlocateEnemyCharacter();
    }
    else
    {
        AlocatePlayerCharacter();
    }
}

void BattleField::AlocateEnemyCharacter()
{
    
    int random = GetRandomInt(0, grid->grids.size());
    auto l_front = grid->grids.begin();

    advance(l_front, random);

    Types::GridBox* RandomLocation = &*l_front;
    
    if (!RandomLocation->ocupied)
    {
        EnemyCurrentLocation = &*l_front;
        l_front->ocupied = true;
        EnemyCharacter->currentBox = *l_front;
        grid->drawBattlefield(5, 5);
    }
    else
    {
        AlocateEnemyCharacter();
    }


}