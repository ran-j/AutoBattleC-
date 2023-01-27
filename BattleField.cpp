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
#include <functional>

using namespace std;

BattleField::BattleField()
{
    engine = new (Engine);
    PlayersQueue = list<shared_ptr<Character>>();
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
    currentTurn = 0;
    Engine::DrawText("Inform battlefield Lines:\n");
    int bfLines = 0;
    cin >> bfLines;

    Engine::DrawText("Inform battlefield Columns:\n");
    int bfColumns = 0;
    cin >> bfColumns;

    engine->Init(bfLines, bfColumns);

    // asks for the player to choose between for possible classes via console.
    Engine::DrawText("Choose Between One of this Classes:\n");
    Engine::DrawText("[1] Paladin, [2] Warrior, [3] Cleric, [4] Archer \n");

    int classIndex = 0;
    cin >> classIndex;

    if (classIndex < 1 || classIndex > 4)
    {
        Engine::DrawText("Invalid Class, try again.\n");
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

    PlayersQueue.push_back(PlayerCharacter);
    PlayersQueue.push_back(enemy1);
    PlayersQueue.push_back(enemy2);
    PlayersQueue.push_back(assistant);
}

std::shared_ptr<Character> BattleField::FindCharacterWithDifferentTags(const char *team)
{
    auto targetInterator = find_if(PlayersQueue.begin(), PlayersQueue.end(), [&](const shared_ptr<Character> &otherCharacter)
                                   { return otherCharacter->Team != team && otherCharacter->IsDead() == false; });

    shared_ptr<Character> foundTarget;
    if (targetInterator != PlayersQueue.end())
    {
        foundTarget = *targetInterator;
    }
    return foundTarget;
}

std::shared_ptr<Character> BattleField::FindCharacterWithSameTags(const char *team)
{
    auto targetInterator = find_if(PlayersQueue.begin(), PlayersQueue.end(), [&](const shared_ptr<Character> &otherCharacter)
                                   { return otherCharacter->Team == team && otherCharacter->IsDead() == false; });

    shared_ptr<Character> enemyTarget;
    if (targetInterator != PlayersQueue.end())
    {
        enemyTarget = *targetInterator;
    }
    return enemyTarget;
}

void BattleField::StartTurn()
{
    Engine::DrawText("\nLogs:\n");
    for (auto it = PlayersQueue.begin(); it != PlayersQueue.end(); ++it)
    {
        std::shared_ptr<Character> currentCharacter = (*it);

        currentCharacter->ProcessStatusEffects();

        if (currentCharacter->IsDead())
        {
            continue;
        }

        std::shared_ptr<Character> enemyTarget = FindCharacterWithDifferentTags(currentCharacter->Team);

        if (enemyTarget == nullptr)
        {
            continue;
        }
        bool isEnemyNear = engine->IsCloseToTarget(currentCharacter, enemyTarget);
        currentCharacter->PlayTurn(isEnemyNear, enemyTarget, [&]() { 
            engine->MoveActorToTarget(currentCharacter, enemyTarget);
        });

        Engine::DrawText(" ");
    }

    currentTurn++;
    HandleTurn();
}

void BattleField::HandleTurn()
{
    Engine::DrawText("\n");
    auto it = PlayersQueue.begin();
    while (it != PlayersQueue.end())
    {
        std::shared_ptr<Character> currentCharacter = (*it);
        if (currentCharacter->IsDead())
        {
            if (currentCharacter->Id == PlayerCharacter->Id)
            {
                engine->ClearCanvas();
                engine->Stop();
                Engine::DrawText("\nYOU DIED\n");
                Engine::WaitInput();
                return;
            }
            else
            {
                engine->DestroyActor(currentCharacter);
                Engine::DrawText("Enemy %s was slayed", currentCharacter->Id);
                it = PlayersQueue.erase(it);
            }
        }
        else
        {
            currentCharacter->DecreaseStatusEffects();
            Engine::DrawText("%s still has %f life points \t", currentCharacter->Id, currentCharacter->Health);
            it++;
        }
    }

    if (!FindCharacterWithDifferentTags(PlayerCharacter->Team))
    {
        engine->ClearCanvas();
        engine->Stop();
        Engine::DrawText("\nYou Win, thanks for play.\n");
        Engine::WaitInput();
        return;
    }

    Engine::DrawText("\n#### End of turn %d, click on any key to start the next turn... #### \n", currentTurn);

    Engine::WaitInput();
}