#include "Engine.h"
#include "Actor.h"
#include "Utils.h"

#include <algorithm>
#include <list>
#include <random>
 
Engine::Engine()
{
    grid = new Grid();
}

void Engine::Init(int lines, int Columns)
{
    mLines = lines;
    mColumns = Columns;
    grid->Init(lines, Columns);
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
    if (!bHasChanges)
    {
        return;
    }

    ClearCanvas();

    for (int i = 0; i < mLines; i++)
    {
        for (int j = 0; j < mColumns; j++)
        {
            int index = (mColumns * i + j);
            Types::GridBox *currentGrid = &grid->grids[index];

            if (currentGrid->ocupied)
            {
                std::shared_ptr<Actor> target = Actors[index];
                if (target)
                {
                    printf("[%s]\t", target->GetSprite());
                }
                else
                {
                    printf("[X]\t");
                }
            }
            else
            {
                printf("[ ]\t");
            }
        }
        printf("\n");
    }
    printf("\n");

    bHasChanges = false;
}

void Engine::SpawnActor(std::shared_ptr<Actor> target)
{
    //get a random position in the grid
    std::random_device rd;
    std::mt19937 g(rd());
    auto possibleGrid = std::next(grid->grids.begin(), std::uniform_int_distribution<int>(0, grid->grids.size()-1)(g));

    if (!possibleGrid->ocupied)
    {
        possibleGrid->ocupied = true;
        SetActorIndex(target, possibleGrid->Index);
        bHasChanges = true;
    }
    else
    {
        SpawnActor(target);
    }
}

void Engine::DestroyActor(std::shared_ptr<Actor> target)
{
    auto actorCurrentGrid = GetActorGrid(target);
    actorCurrentGrid->ocupied = false;
    Actors.erase(actorCurrentGrid->Index);
    ActorsWorldPositions.erase(target->Id);
    bHasChanges = true;
}

int Engine::GetActorLocation(std::shared_ptr<Actor> target)
{
    return ActorsWorldPositions[target->Id];
}

std::vector<Types::GridBox>::iterator Engine::GetActorGrid(std::shared_ptr<Actor> target)
{
    int targetCurrentIndex = GetActorLocation(target);
    auto targetCurrentGrid = grid->grids.begin();
    advance(targetCurrentGrid, targetCurrentIndex);
    return targetCurrentGrid;
}

void Engine::MoveActorToTarget(std::shared_ptr<Actor> actor, std::shared_ptr<Actor> target)
{
    int gridSize = GetWorldSize();
    auto actorCurrentGrid = GetActorGrid(actor);
    auto targetCurrentGrid = GetActorGrid(target);

    int newIndex = GetMoveDirection(actorCurrentGrid->xIndex, actorCurrentGrid->yIndex, targetCurrentGrid->xIndex, targetCurrentGrid->yIndex, actorCurrentGrid->Index);

    if (newIndex >= 0 && newIndex <= gridSize)
    {
        // leave the current grid
        actorCurrentGrid->ocupied = false;
        // Update locations maps
        SetActorIndex(actor, newIndex);
        // enter in grid
        grid->grids[newIndex].ocupied = true;
        // notify that has changes in grid
        bHasChanges = true;
        return;
    }
}

int Engine::GetMoveDirection(int xIndex, int yIndex1, int xIndex2, int yIndex2, int gridIndex)
{
    if (xIndex < xIndex2) // Move right
    {
        return gridIndex + 1;
    }
    else if (xIndex > xIndex2) // Move left
    {
        return gridIndex - 1;
    }

    //TODO there is a bug here
    if (yIndex1 < yIndex2) // Move up
    {
        return gridIndex - mLines;
    }
    else if (yIndex1 > yIndex2) // move down
    {
        return gridIndex + mLines;
    }

    return -1;
}

void Engine::SetActorIndex(std::shared_ptr<Actor> target, int index)
{
    Actors[index] = target;
    ActorsWorldPositions[target->Id] = index;
}

bool Engine::IsCloseToTarget(std::shared_ptr<Actor> actor, std::shared_ptr<Actor> target)
{
    auto actorCurrentGrid = GetActorGrid(actor);
    auto targetCurrentGrid = GetActorGrid(target);

    double dist = Utils::DistanceTo(actorCurrentGrid->xIndex, actorCurrentGrid->yIndex, targetCurrentGrid->xIndex, targetCurrentGrid->yIndex);
    double oneTileDistance = 1;

    return dist <= oneTileDistance;
}