#include "WorldMatrix.h"

#include "Actor.h"
#include "Utils.h"

WorldMatrix::WorldMatrix()
{
    grid = new Grid();
}

void WorldMatrix::Init(int lines, int Columns)
{
    mLines = lines;
    mColumns = Columns;
    grid->Init(lines, Columns);
}

int WorldMatrix::GetActorLocation(std::shared_ptr<Actor> target)
{
    return ActorsWorldPositions[target->Id];
}

std::vector<Types::GridBox>::iterator WorldMatrix::GetActorGrid(std::shared_ptr<Actor> target)
{
    int targetCurrentIndex = GetActorLocation(target);
    auto targetCurrentGrid = grid->grids.begin();
    advance(targetCurrentGrid, targetCurrentIndex);
    return targetCurrentGrid;
}

void WorldMatrix::MoveActorToTarget(std::shared_ptr<Actor> actor, std::shared_ptr<Actor> target)
{
    int gridSize = GetWorldSize();
    auto actorCurrentGrid = GetActorGrid(actor);
    auto targetCurrentGrid = GetActorGrid(target);

    int newIndex = GetMoveDirection(actorCurrentGrid->Line, targetCurrentGrid->Line, actorCurrentGrid->Column, targetCurrentGrid->Column, actorCurrentGrid->Index);
    int processedIndex = GetNextFreeIndex(newIndex, actorCurrentGrid->Index);

    if (processedIndex >= 0 && processedIndex < gridSize)
    {
        // leave the current grid
        actorCurrentGrid->occupied = false;
        // Update locations maps
        SetActorIndex(actor, processedIndex, actorCurrentGrid->Index);
        // enter in grid
        grid->grids[processedIndex].occupied = true;
        bHasChanges = true;
        return;
    }
}

int WorldMatrix::GetNextFreeIndex(int newIndex, int currentIndex)
{
    if (grid->grids[newIndex].occupied)
    {
        int maxIndex = GetWorldSize();
        int upGrid = newIndex - mLines;
        int downGrid = newIndex + mLines;
        int leftGrid = newIndex + 1;
        int rightGrid = newIndex + 1;

        if (upGrid != currentIndex && !grid->grids[upGrid].occupied && upGrid >= 0 && upGrid < maxIndex)
        {
            return upGrid;
        }
        if (downGrid != currentIndex && !grid->grids[downGrid].occupied && downGrid >= 0 && downGrid < maxIndex)
        {
            return downGrid;
        }
        if (leftGrid != currentIndex && !grid->grids[leftGrid].occupied && leftGrid >= 0 && leftGrid < maxIndex)
        {
            return leftGrid;
        }
        if (rightGrid != currentIndex && !grid->grids[rightGrid].occupied && rightGrid >= 0 && rightGrid < maxIndex)
        {
            return rightGrid;
        }
    }
    return newIndex;
}

int WorldMatrix::GetMoveDirection(int Line, int Line2, int Column1, int Column2, int gridIndex)
{

    if (Column1 == Column2) // they are at the same level, should choose move up or down
    {
        if (Line > Line2) // up
        {
            return gridIndex - mLines;
        }
        if (Line < Line2) // down
        {
            return gridIndex + mLines;
        }
    }

    if (Column1 > Column2) // move right
    {
        return gridIndex - 1;
    }

    if (Column1 < Column2) // move left
    {
        return gridIndex + 1;
    }

    return -1;
}

void WorldMatrix::SetActorIndex(std::shared_ptr<Actor> target, int index, int previousIndex)
{
    // Delete previous position
    if (previousIndex >= 0)
    {
        Actors.erase(previousIndex);
    }
    ActorsWorldPositions.erase(target->Id);
    // added new position on track lists
    Actors[index] = target;
    ActorsWorldPositions[target->Id] = index;
}

bool WorldMatrix::IsCloseToTarget(std::shared_ptr<Actor> actor, std::shared_ptr<Actor> target, double distance)
{
    auto actorCurrentGrid = GetActorGrid(actor);
    auto targetCurrentGrid = GetActorGrid(target);

    double dist = Utils::DistanceTo(actorCurrentGrid->Line, actorCurrentGrid->Column, targetCurrentGrid->Line, targetCurrentGrid->Column);
    return dist <= distance;
}

void WorldMatrix::MoveActorToIndex(std::shared_ptr<Actor> actor, int index)
{
    if (index > GetWorldSize())
    {
        return;
    }
    if (!grid->grids[index].occupied)
    {
        auto actorCurrentGrid = GetActorGrid(actor);
        grid->grids[actorCurrentGrid->Index].occupied = false;
        grid->grids[index].occupied = true;
        SetActorIndex(actor, index, actorCurrentGrid->Index);
    }
    else
    {
        MoveActorToIndex(actor, index + 1); // Danger check this later
    }
}