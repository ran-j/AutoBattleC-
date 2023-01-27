#include "Engine.h"
#include "Actor.h"
#include "Utils.h"

#include <stdarg.h>

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
    // maybe add a unique pointer ref in grids to character

    int random = Utils::GetRandomInt(0, GetWorldSize());
    auto l_front = grid->grids.begin();
    advance(l_front, random);

    if (!l_front->ocupied)
    {
        l_front->ocupied = true;
        SetActorIndex(target, random);
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

// TODO this can be better
void Engine::MoveActorToTarget(std::shared_ptr<Actor> actor, std::shared_ptr<Actor> target)
{
    int gridSize = GetWorldSize();
    auto actorCurrentGrid = GetActorGrid(actor);
    auto targetCurrentGrid = GetActorGrid(target);

    if (actorCurrentGrid->xIndex < targetCurrentGrid->xIndex) // Move right
    {
        int newIndex = actorCurrentGrid->Index + 1;
        if (newIndex >= 0 && newIndex < gridSize)
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
    else if (actorCurrentGrid->xIndex > targetCurrentGrid->xIndex) // Move left
    {
        int newIndex = actorCurrentGrid->Index - 1;
        if (newIndex >= 0 && newIndex < gridSize)
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

    if (actorCurrentGrid->yIndex < targetCurrentGrid->yIndex) // Move up
    {
        int newIndex = actorCurrentGrid->Index - mLines;
        if (newIndex >= 0 && newIndex < gridSize)
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
    else if (actorCurrentGrid->yIndex > targetCurrentGrid->yIndex) // move down
    {
        int newIndex = actorCurrentGrid->Index + mLines;
        if (newIndex >= 0 && newIndex < gridSize)
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
}

void Engine::SetActorIndex(std::shared_ptr<Actor> target, int index)
{
    Actors[index] = target;
    ActorsWorldPositions[target->Id] = index;
}

bool Engine::IsCloseToTarget(std::shared_ptr<Actor> actor, std::shared_ptr<Actor>target)
{
    auto actorCurrentGrid = GetActorGrid(actor);
    auto targetCurrentGrid = GetActorGrid(target);
   
    double dist = Utils::DistanceTo(actorCurrentGrid->xIndex, actorCurrentGrid->yIndex, targetCurrentGrid->xIndex, targetCurrentGrid->yIndex);
    double oneTileDistance = 1;
     
    return dist <= oneTileDistance;
}

void Engine::DrawText(const char* format, ...) 
{
    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    printf("\n");
    va_end(args);

    //wait input to proceed
    WaitInput();
    bHasChanges = true;
}