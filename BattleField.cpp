#include "BattleField.h"

#include "Types.h"
#include "Character.h"
#include "Engine.h"

#include <iostream>
#include <list>
#include <string>
#include <cstdlib>

using namespace std;

BattleField::BattleField()
{
    engine = new (Engine);
}

void BattleField::Init()
{
    //TODO player should inform the grid size
    engine->Init(5, 5);

    SetUpGame();

    while (!engine->ShouldQuit())
    {
        engine->Draw();
    }

    return;
}

void BattleField::SetUpGame()
{
    // asks for the player to choose between for possible classes via console.
    printf("Choose Between One of this Classes:\n");
    printf("[1] Paladin, [2] Warrior, [3] Cleric, [4] Archer \n");

    int classIndex = 0;
    cin >> classIndex;

    switch (classIndex)
    {
    case 1:
    case 2:
    case 3:
    case 4:
        bPlayerActFirst = GetRandomInt(0, 1);

        PlayerCharacter = CreateCharacter(classIndex, 100, 20, "player", "P");
        engine->InsertActor(PlayerCharacter);

        int randomClass = GetRandomInt(1, 4);
        EnemyCharacter = CreateCharacter(randomClass, 100, 20, "enemy1", "E");
        engine->InsertActor(EnemyCharacter);

        CharacterAndTargets[PlayerCharacter] = EnemyCharacter;
        CharacterAndTargets[EnemyCharacter] = PlayerCharacter;

        break;
    default:
        SetUpGame();
        break;
    }
}

Character *BattleField::CreateCharacter(int classIndex, float health, float baseDamage, const char* id, const char* sprite)
{
    Types::CharacterClass characterClass = (Types::CharacterClass)classIndex;
    auto PlayerCharacter = new Character(characterClass);
    PlayerCharacter->Health = health;
    PlayerCharacter->BaseDamage = baseDamage;
    PlayerCharacter->Id = id;
    PlayerCharacter->Sprite = sprite;
}

void BattleField::StartTurn()
{
    auto playerTarget = CharacterAndTargets[PlayerCharacter];
    auto enemyTarget = CharacterAndTargets[EnemyCharacter];

    //TODO decide if should move or attack or heal it self. if attacks decide if should use a special skill

    //TODO hahahaha this can be far far better
    if (bPlayerActFirst)
    {
        engine->MoveActorToTarget(PlayerCharacter, playerTarget);
        engine->MoveActorToTarget(EnemyCharacter, enemyTarget);
    }
    else 
    {
        engine->MoveActorToTarget(EnemyCharacter, enemyTarget);
        engine->MoveActorToTarget(PlayerCharacter, playerTarget);
    }

    currentTurn++;
    HandleTurn();
}

void BattleField::HandleTurn()
{
    if (PlayerCharacter->IsDead())
    {
        printf("YOU DIED");
    }
    else if (EnemyCharacter->IsDead())
    {
        printf("Enemy slayed");
    }
    else{
        printf("\n");
        printf("Click on any key to start the next turn...\n");
        printf("\n");

        #ifdef __linux__ 
            system("read"); 
        #elif _WIN32
            system("pause");
        #endif       
    }
}

// TODO move this to utils
int BattleField::GetRandomInt(int min, int max)
{
    int range = max - min + 1;
    return rand() % range + min;
}