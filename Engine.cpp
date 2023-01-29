#include "Engine.h"
#include "Actor.h"
#include "Utils.h"
#include "WorldMatrix.h"

#include <algorithm>
#include <list>
#include <random>

Engine::Engine()
{
    worldMatrix = std::make_shared<WorldMatrix>();
}

void Engine::Init(int lines, int Columns)
{
    worldMatrix->Init(lines, Columns);
    bHasChanges = true;
}

void Engine::ClearCanvas()
{
#ifdef __linux__
    system("clear");
#elif _WIN32
    system("cls");
#endif
}

void Engine::Draw()
{
    if (bShouldQuit)
    {
        return;
    }
    if (!bHasChanges && !worldMatrix->bHasChanges)
    {
        return;
    }

    // ClearCanvas();

    for (int i = 0; i < worldMatrix->mLines; i++)
    {
        for (int j = 0; j < worldMatrix->mColumns; j++)
        {
            int index = (worldMatrix->mColumns * i + j);
            Types::GridBox *currentGrid = &worldMatrix->grid->grids[index];

            if (currentGrid->occupied)
            {
                std::shared_ptr<Actor> target = worldMatrix->Actors[index];
                if (target)
                {
                    printf("[%s]\t", target->GetSprite());
                    // printf("[%s %d %d %d]\t", target->GetSprite(), index, i, j);
                }
                else
                {
                    //This should never happen
                    printf("[?]\t");
                }
            }
            else
            {
                printf("[ ]\t");
                // printf("[ %d %d %d]\t", index, i, j);
            }
        }
        printf("\n");
    }
    printf("\n");

    bHasChanges = false;
    worldMatrix->bHasChanges = false;
}

void Engine::SpawnActor(std::shared_ptr<Actor> target)
{
    // get a random position in the grid
    std::random_device rd;
    std::mt19937 g(rd());
    auto possibleGrid = std::next(worldMatrix->grid->grids.begin(), std::uniform_int_distribution<int>(0, worldMatrix->grid->grids.size() - 1)(g));

    if (!possibleGrid->occupied)
    {
        possibleGrid->occupied = true;
        worldMatrix->SetActorIndex(target, possibleGrid->Index, -1);
        target->worldMatrix = worldMatrix;
        bHasChanges = true;
    }
    else
    {
        SpawnActor(target);
    }
}

void Engine::DestroyActor(std::shared_ptr<Actor> target)
{
    auto actorCurrentGrid = worldMatrix->GetActorGrid(target);
    actorCurrentGrid->occupied = false;
    worldMatrix->Actors.erase(actorCurrentGrid->Index);
    worldMatrix->ActorsWorldPositions.erase(target->Id);
    bHasChanges = true;
}