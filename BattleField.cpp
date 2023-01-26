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
    TurnQueue = list<shared_ptr<Character>>();
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
        PlayerCharacter = CreateCharacter(classIndex, 100, 200, "Hero", "P");
        engine->SpawnActor(PlayerCharacter);

        EnemyCharacter = CreateCharacter(GetRandomInt(1, 4), 100, 20, "Evil Man 1", "E");
        engine->SpawnActor(EnemyCharacter);

        CharacterAndTargets[PlayerCharacter] = EnemyCharacter;
        CharacterAndTargets[EnemyCharacter] = PlayerCharacter;

        TurnQueue.push_back(PlayerCharacter);
        TurnQueue.push_back(EnemyCharacter);

        // shuffle list to prevent player or enemy always init first
        // std::shuffle(TurnQueue.begin(), TurnQueue.end(), std::mt19937{ std::random_device{}() }); //wtf this gives me a error

        // HAHAHAHAHHAHA SHOULD I ????
        //  std::sort(TurnQueue.begin(), TurnQueue.end(), [](const std::shared_ptr<Character> a, const std::shared_ptr<Character> b) {
        //      int aLength = std::strlen(a->Id);
        //      int bLength = std::strlen(b->Id);
        //      return aLength < bLength;
        //  });

        break;
    default:
        SetUpGame();
        break;
    }
}

std::shared_ptr<Character> BattleField::CreateCharacter(int classIndex, float health, float baseDamage, const char *id, const char *sprite)
{
    Types::CharacterClass characterClass = (Types::CharacterClass)classIndex;
    auto PlayerCharacter = std::make_shared<Character>(characterClass);
    PlayerCharacter->Health = health;
    PlayerCharacter->BaseDamage = baseDamage;
    PlayerCharacter->DamageMultiplier = GetRandomFloat(0.2, 1.0); // TODO class influence in life and damage
    PlayerCharacter->Id = id;
    PlayerCharacter->Sprite = sprite;
    return PlayerCharacter;
}

void BattleField::StartTurn()
{
    printf("\nLogs: \n");
    for (auto it = TurnQueue.begin(); it != TurnQueue.end(); ++it)
    {
        std::shared_ptr<Character> currentCharacter = (*it);
        std::shared_ptr<Character> enemyTarget = CharacterAndTargets[currentCharacter];

        if (currentCharacter->IsDead())
        {
            continue;
        }
        
        // TODO decide if should move or attack or heal it self. if attacks decide if should use a special skill
        if (engine->IsCloseToTarget(currentCharacter, enemyTarget))
        {
            Types::ActionType action = currentCharacter->GetActionWhenNearEnemy();
            switch (action)
            {
            case Types::ActionType::Attack:
                HandleCombat(currentCharacter, enemyTarget);
                break;
            default:
                engine->DrawText("%s is to confused to act", currentCharacter->Id);
                break;
            }
        }
        else
        {
            engine->MoveActorToTarget(currentCharacter, enemyTarget);
            engine->DrawText("%s move one tile", currentCharacter->Id);
        }
    }

    currentTurn++;
    HandleTurn();
}

void BattleField::HandleCombat(std::shared_ptr<Character>attacker, std::shared_ptr<Character>target)
{
    engine->DrawText("%s launch a attack in %s", attacker->Id, target->Id);
    // attack target
    float damage = attacker->Attack(target);
    // check if miss attack
    if (damage == 0)
    {
        engine->DrawText("%s miss the attack.", attacker->Id, target->Id);
    }
    else
    {
        // log result
        engine->DrawText("%s inflate %f in %s with bare hands", attacker->Id, damage, target->Id); // TODO each class have a different attack
    }
}

void BattleField::HandleTurn()
{
    if (PlayerCharacter->IsDead())
    {
        engine->ClearCanvas();
        engine->Stop();
        printf("\nYOU DIED\n");
        engine->WaitInput();
    }
    else if (EnemyCharacter->IsDead())
    {
        printf("\nEnemy slayed\n");
        engine->WaitInput();
        engine->ClearCanvas();
        engine->Stop();
        printf("\nYou Win, thanks for play.\n");
        engine->WaitInput();
    }
    else
    {
        printf("\n");
        printf("#### End of turn, click on any key to start the next turn... #### \n");
        printf("\n");

        engine->WaitInput();
    }
}

// TODO move this to utils
int BattleField::GetRandomInt(int min, int max)
{
    int range = max - min + 1;
    return rand() % range + min;
}

// TODO move this to utils
float BattleField::GetRandomFloat(float min, float max)
{
    return max + (rand() / (RAND_MAX / (min - max)));
}