#include "BattleField.h"

#include "Types.h"
#include "Character.h"
#include "Engine.h"

#include <iostream>
#include <list>
#include <string>
#include <cstdlib>
#include <random>
#include <algorithm>

using namespace std;

BattleField::BattleField()
{
    engine = new (Engine);
}

void BattleField::Init()
{
    SetUpGame();

    while (!engine->ShouldQuit())
    {
        engine->Draw();
        StartTurn();
    }

    return;
}

void BattleField::SetUpGame()
{
    printf("Inform battlefield Lines:\n");
    int bfLines = 0;
    cin >> bfLines;

    printf("Inform battlefield Columns:\n");
    int bfColumns = 0;
    cin >> bfColumns;

    engine->Init(bfLines, bfColumns);

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
        PlayerCharacter = CreateCharacter(classIndex, 100, 20, "player", "P");
        engine->SpawnActor(PlayerCharacter);

        EnemyCharacter = CreateCharacter(GetRandomInt(1, 4), 100, 20, "enemy1", "E");
        engine->SpawnActor(EnemyCharacter);

        CharacterAndTargets[PlayerCharacter] = EnemyCharacter;
        CharacterAndTargets[EnemyCharacter] = PlayerCharacter;

        TurnQueue.push_back(PlayerCharacter);
        TurnQueue.push_back(EnemyCharacter);

        //shuffle list to prevent player or enemy always init first
        //std::shuffle(TurnQueue.begin(), TurnQueue.end(), std::mt19937{ std::random_device{}() }); //wtf this gives me a error

        //HAHAHAHAHHAHA SHOULD I ????
        // std::sort(TurnQueue.begin(), TurnQueue.end(), [](const Character* a, const Character* b) {
        //     int aLength = std::strlen(a->Id);
        //     int bLength = std::strlen(b->Id);
        //     return aLength < bLength;
        // });
 
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
    return PlayerCharacter;
}

void BattleField::StartTurn()
{

    for (auto it = TurnQueue.begin(); it != TurnQueue.end(); ++it) {
        auto currentCharacter = (*it);
        auto enemyTarget = CharacterAndTargets[currentCharacter];
        
        //TODO decide if should move or attack or heal it self. if attacks decide if should use a special skill
        engine->MoveActorToTarget(currentCharacter, enemyTarget);
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