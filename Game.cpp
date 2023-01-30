#include "Game.h"

#include "Types.h"
#include "Character.h"
#include "Engine.h"
#include "Utils.h"
#include "ConstructorHelper.h"
#include "Colors.h"

#include <iostream>
#include <list>
#include <random>
#include <algorithm>
#include <assert.h>
#include <functional>

using namespace std;

Game::Game()
{
    engine = new (Engine);
    PlayersQueue = list<shared_ptr<Character>>();
}

void Game::Init()
{
    SetUpGame();

    engine->ClearViewPort();

    while (!engine->ShouldQuit())
    {
        engine->Draw();
        StartTurn();
        engine->Draw();
        HandleTurn();
    }

    return;
}

void Game::SetUpGame()
{
    currentTurn = 0;
    Engine::DrawText("Inform battlefield Lines:\n");
    int bfLines = 0;
    cin >> bfLines;

    Engine::DrawText("Inform battlefield Columns:\n");
    int bfColumns = 0;
    cin >> bfColumns;

    if (bfLines < 4 || bfColumns < 4)
    {
        Engine::DrawText("Invalid battlefield size, try again.\n");
        return SetUpGame();
    }

    engine->Init(bfLines, bfColumns);

    // asks for the player to choose between for possible classes via console.
    Engine::DrawText("Choose Between One of this Classes:\n");
    Engine::DrawText("[1] Paladin, [2] Warrior, [3] Cleric, [4] Archer \n");

    int classIndex = 0;
    cin >> classIndex;

    if (classIndex < 1 || classIndex > 4)
    {
        Engine::DrawText("Invalid Class, try again.\n");
        return SetUpGame();
    }

    PlayerCharacter = ConstructorHelper::MakeCharacter(classIndex, 100, 20, "You", GREEN("P"), "HEROES");
    engine->SpawnActor(PlayerCharacter);

    auto assistant = ConstructorHelper::MakeCharacter(Utils::GetRandomInt(1, 4), 50, 20, "Your assistant", BLUE("A"), "HEROES");
    engine->SpawnActor(assistant);

    auto enemy1 = ConstructorHelper::MakeCharacter(Utils::GetRandomInt(1, 4), 100, 20, "Enemy 1", RED("E"), "CPUE");
    engine->SpawnActor(enemy1);

    auto enemy2 = ConstructorHelper::MakeCharacter(Utils::GetRandomInt(1, 4), 90, 20, "Enemy 2", BRIGHTRED("E"), "CPUE");
    engine->SpawnActor(enemy2);

    PlayersQueue.push_back(PlayerCharacter);
    PlayersQueue.push_back(enemy1);
    PlayersQueue.push_back(enemy2);
    PlayersQueue.push_back(assistant);
}

std::shared_ptr<Character> Game::FindCharacterWithDifferentTags(const char *team)
{
    auto targetInterator = find_if(PlayersQueue.begin(), PlayersQueue.end(), [&](const shared_ptr<Character> &otherCharacter)
                                   { return otherCharacter->Team != team &&
                                            otherCharacter->IsDead() == false &&
                                            otherCharacter->Id != PlayerCharacter->Id &&
                                            otherCharacter->bIsHiddenInGame == false; });

    shared_ptr<Character> foundTarget;
    if (targetInterator != PlayersQueue.end())
    {
        foundTarget = *targetInterator;
    }
    return foundTarget;
}

std::shared_ptr<Character> Game::FindCharacterWithSameTags(const char *team)
{
    auto targetInterator = find_if(PlayersQueue.begin(), PlayersQueue.end(), [&](const shared_ptr<Character> &otherCharacter)
                                   { return otherCharacter->Team == team &&
                                            otherCharacter->IsDead() == false &&
                                            otherCharacter->Id != PlayerCharacter->Id; });

    shared_ptr<Character> enemyTarget;
    if (targetInterator != PlayersQueue.end())
    {
        enemyTarget = *targetInterator;
    }
    return enemyTarget;
}

void Game::StartTurn()
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

        currentCharacter->PlayTurn(enemyTarget);

        Engine::DrawText(" \t ");
    }

    currentTurn++;
}

void Game::HandleTurn()
{
    Engine::DrawText("\n#### End of turn %d ####", currentTurn);

    auto it = PlayersQueue.begin();
    while (it != PlayersQueue.end())
    {
        std::shared_ptr<Character> currentCharacter = (*it);
        if (currentCharacter->IsDead())
        {
            if (currentCharacter->Id == PlayerCharacter->Id)
            {
                Engine::DrawText("\nYOU DIED\n");
                Engine::WaitInput();
                engine->Stop();
                return;
            }
            else
            {
                engine->DestroyActor(currentCharacter);
                Engine::DrawText("%s was killed", currentCharacter->Id);
                it = PlayersQueue.erase(it);
            }
        }
        else
        {
            currentCharacter->DecreaseStatusEffects();
            Engine::DrawText("%s still has %f life points", currentCharacter->Id, currentCharacter->Health);
            it++;
        }
    }

    if (!FindCharacterWithDifferentTags(PlayerCharacter->Team))
    {
        Engine::DrawText("\nYou Win, thanks for play.\n");
        PlayerCharacter->WinGame();
        engine->Stop();
        Engine::WaitInput();
        return;
    }

    Engine::WaitInput();
    engine->ClearViewPort();
}