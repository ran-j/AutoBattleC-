#include "BattleField.h"

#include "Types.h"
#include "Character.h"
#include "Engine.h"
#include "Utils.h"
#include "ConstructorHelper.h"

#include <iostream>
#include <list>
#include <random>
#include <algorithm>
#include <assert.h>

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

    if (classIndex < 1 || classIndex > 4)
    {
        printf("Invalid Class, try again.\n");
        SetUpGame();
    }

    PlayerCharacter = ConstructorHelper::CreateCharacter(classIndex, 100, 20, "Hero", "P", "HEROES");
    engine->SpawnActor(PlayerCharacter);

    auto assistant = ConstructorHelper::CreateCharacter(Utils::GetRandomInt(1, 4), 50, 20, "Hero assistant", "A", "HEROES");
    engine->SpawnActor(assistant);

    auto enemy1 = ConstructorHelper::CreateCharacter(Utils::GetRandomInt(1, 4), 100, 20, "Evil Man 1", "E", "CPUE");
    engine->SpawnActor(enemy1);

    auto enemy2 = ConstructorHelper::CreateCharacter(Utils::GetRandomInt(1, 4), 90, 20, "Evil Man 2", "E", "CPUE");
    engine->SpawnActor(enemy2);

    TurnQueue.push_back(PlayerCharacter);
    TurnQueue.push_back(enemy1);
    TurnQueue.push_back(enemy2);
    TurnQueue.push_back(assistant);
}

std::shared_ptr<Character> BattleField::FindCharacterWithDifferentTags(const char *team)
{
    auto targetInterator = find_if(TurnQueue.begin(), TurnQueue.end(), [&](const shared_ptr<Character> &otherCharacter)
                                  { return otherCharacter->Team != team && otherCharacter->IsDead() == false; });

    shared_ptr<Character> foundTarget;
    if (targetInterator != TurnQueue.end())
    {
        foundTarget = *targetInterator;
    }
    return foundTarget;
}

std::shared_ptr<Character> BattleField::FindCharacterWithSameTags(const char *team)
{
    auto targetInterator = find_if(TurnQueue.begin(), TurnQueue.end(), [&](const shared_ptr<Character> &otherCharacter)
                                  { return otherCharacter->Team == team && otherCharacter->IsDead() == false; });

    shared_ptr<Character> enemyTarget;
    if (targetInterator != TurnQueue.end())
    {
        enemyTarget = *targetInterator;
    }
    return enemyTarget;
}

void BattleField::StartTurn()
{
    printf("\nLogs:\n");
    for (auto it = TurnQueue.begin(); it != TurnQueue.end(); ++it)
    {
        std::shared_ptr<Character> currentCharacter = (*it);
        
        std::list<const char *> textEffects = currentCharacter->ProcessStatusEffects();

        for (auto text : textEffects) {
            engine->DrawText(text); 
        } 

        if (currentCharacter->IsDead())
        {
            continue;
        }
       
        std::shared_ptr<Character> enemyTarget = FindCharacterWithDifferentTags(currentCharacter->Team);

        if (enemyTarget == nullptr)
        {
            continue;
        }

        //TODO maybe this should be in actor class called PlayTurn(bool isNearTarget, Character* target) function
        if (engine->IsCloseToTarget(currentCharacter, enemyTarget))
        {
            Types::ActionType action = currentCharacter->GetActionWhenNearEnemy();
            switch (action)
            {
            case Types::ActionType::Attack:
                if (!currentCharacter->CanMove())
                {
                    engine->DrawText("%s can't attack.", currentCharacter->Id);
                    continue;
                }
                HandleCombat(currentCharacter, enemyTarget);
                break;
            default:
                engine->DrawText("%s is to confused to act", currentCharacter->Id);
                break;
            }
        }
        else
        {
            if (!currentCharacter->CanMove())
            {
                engine->DrawText("%s can't move.", currentCharacter->Id);
                continue;
            }

            engine->MoveActorToTarget(currentCharacter, enemyTarget);
            engine->DrawText("%s move one tile", currentCharacter->Id);
        }
    }

    currentTurn++;
    HandleTurn();
}

void BattleField::HandleCombat(std::shared_ptr<Character> attacker, std::shared_ptr<Character> target)
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
    auto it = TurnQueue.begin();
    while (it != TurnQueue.end())
    {
        std::shared_ptr<Character> currentCharacter = (*it);
        if (currentCharacter->IsDead())
        {
            if (currentCharacter->Id == PlayerCharacter->Id)
            {
                engine->ClearCanvas();
                engine->Stop();
                printf("\nYOU DIED\n");
                engine->WaitInput();
                return;
            }
            else
            {
                engine->DestroyActor(currentCharacter);
                printf("\nEnemy %s slayed\n", currentCharacter->Id);
                it = TurnQueue.erase(it);
            }
        }
        else
        {
            currentCharacter->DecreaseStatusEffects();
            it++;
        }
    }

    if (!FindCharacterWithDifferentTags(PlayerCharacter->Team))
    {
        engine->ClearCanvas();
        engine->Stop();
        printf("\nYou Win, thanks for play.\n");
        engine->WaitInput();
        return;
    }

    printf("\n");
    printf("#### End of turn, click on any key to start the next turn... #### \n");
    printf("\n");

    engine->WaitInput();
}