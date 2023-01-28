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

    int newIndex = GetMoveDirection(actorCurrentGrid->xIndex, actorCurrentGrid->yIndex, targetCurrentGrid->xIndex, targetCurrentGrid->yIndex, actorCurrentGrid->Index);

    if (newIndex >= 0 && newIndex <= gridSize)
    {
        // leave the current grid
        actorCurrentGrid->ocupied = false;
        // Update locations maps
        SetActorIndex(actor, newIndex);
        // enter in grid
        grid->grids[newIndex].ocupied = true;
        bHasChanges = true;
        return;
    }

}

int WorldMatrix::GetMoveDirection(int xIndex, int yIndex1, int xIndex2, int yIndex2, int gridIndex)
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

void WorldMatrix::SetActorIndex(std::shared_ptr<Actor> target, int index)
{   
    //Delete previous position
    Actors.erase(index);
    ActorsWorldPositions.erase(target->Id);
    //added new position on track lists
    Actors[index] = target;
    ActorsWorldPositions[target->Id] = index;
}

bool WorldMatrix::IsCloseToTarget(std::shared_ptr<Actor> actor, std::shared_ptr<Actor> target, double distance)
{
    auto actorCurrentGrid = GetActorGrid(actor);
    auto targetCurrentGrid = GetActorGrid(target);

    double dist = Utils::DistanceTo(actorCurrentGrid->xIndex, actorCurrentGrid->yIndex, targetCurrentGrid->xIndex, targetCurrentGrid->yIndex);
    return dist <= distance;
}