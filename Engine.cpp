#include "Engine.h"

#include "Actor.h"

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
                Actor *target = Actors[index];
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

void Engine::SpawnActor(Actor *target)
{
    _ASSERT(grid);

    // maybe add a unique pointer ref in grids to character

    int random = GetRandomInt(0, GetWorldSize());
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

int Engine::GetActorLocation(Actor *target)
{
    return ActorsWorldPositions[target->Id];
}

std::vector<Types::GridBox>::iterator Engine::GetActorGrid(Actor *target)
{
    int targetCurrentIndex = GetActorLocation(target);
    auto targetCurrentGrid = grid->grids.begin();
    advance(targetCurrentGrid, targetCurrentIndex);
    return targetCurrentGrid;
}

// TODO this can be better
void Engine::MoveActorToTarget(Actor *actor, Actor *target)
{
    int gridSize = GetWorldSize();
    auto actorCurrentGrid = GetActorGrid(actor);
    auto targetCurrentGrid = GetActorGrid(target);

    auto searchActorInGrids = std::find_if(grid->grids.begin(), grid->grids.end(), [&](const Types::GridBox &box)
                                           { return box.Index == actorCurrentGrid->Index - 1; });

    if (searchActorInGrids != grid->grids.end()) // Move left
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
    else if (actorCurrentGrid->xIndex < targetCurrentGrid->xIndex) // Move right
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
    else if (actorCurrentGrid->yIndex < targetCurrentGrid->yIndex) // move  down
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

void Engine::SetActorIndex(Actor *target, int index)
{
    Actors[index] = target;
    ActorsWorldPositions[target->Id] = index;
}

bool Engine::IsCloseToTarget(Actor *actor, Actor *target)
{
    auto actorCurrentGrid = GetActorGrid(actor);
    auto targetCurrentGrid = GetActorGrid(target);

    if (actorCurrentGrid->xIndex == targetCurrentGrid->xIndex && actorCurrentGrid->yIndex == targetCurrentGrid->yIndex)
    {
        return true;
    }
    else if (actorCurrentGrid->xIndex == targetCurrentGrid->xIndex && actorCurrentGrid->yIndex == targetCurrentGrid->yIndex + 1)
    {
        return true;
    }
    else if (actorCurrentGrid->xIndex == targetCurrentGrid->xIndex && actorCurrentGrid->yIndex == targetCurrentGrid->yIndex - 1)
    {
        return true;
    }
    else if (actorCurrentGrid->xIndex == targetCurrentGrid->xIndex + 1 && actorCurrentGrid->yIndex == targetCurrentGrid->yIndex)
    {
        return true;
    }
    else if (actorCurrentGrid->xIndex == targetCurrentGrid->xIndex - 1 && actorCurrentGrid->yIndex == targetCurrentGrid->yIndex)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// TODO move this to utils
int Engine::GetRandomInt(int min, int max)
{
    int range = max - min + 1;
    return rand() % range + min;
}
