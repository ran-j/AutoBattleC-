//This class is the only one place that handles move actors in world 
//This class does not render anything, just move positions

#pragma once

#include "Grid.h"

#include <map>
#include <memory>

class Actor;

class WorldMatrix
{
public:
    WorldMatrix();

private:
    // list to actor to be draw
    std::map<int, std::shared_ptr<Actor>> Actors;
    // Track of actors position in world
    std::map<const char *, int> ActorsWorldPositions; // should I use unordered_map?
    // world grid
    Grid *grid;

    int mLines = 0;
    int mColumns = 0;

    bool bHasChanges = false;

private:
    void Init(int lines, int Columns);
    // Set Actor Index
    void SetActorIndex(std::shared_ptr<Actor> target, int index, int previousIndex);
    // Get direction base on index
    int GetMoveDirection(int Line, int Line2, int Column1, int Column2, int gridIndex);
    // Get a grid index that is not occupied
    int GetNextFreeIndex(int index, int currentIndex);

public:
    // Return Actor index in world tiles
    int GetActorLocation(std::shared_ptr<Actor> target);
    // Move Actor to a target location
    void MoveActorToTarget(std::shared_ptr<Actor> actor, std::shared_ptr<Actor> target);
    // Move Actor index
    void MoveActorToIndex(std::shared_ptr<Actor> actor, int index);

    // Move Actor to a grid location
    // void MoveActorToTile(std::shared_ptr<Actor> actor, std::vector<Types::GridBox>::iterator target);

    // Check if a actor is close to another target
    bool IsCloseToTarget(std::shared_ptr<Actor> actor, std::shared_ptr<Actor> target, double distance = 1);
    // Return the world tiles size
    inline int GetWorldSize() { return static_cast<int>(grid->grids.size()); }
    // Returns actor current grid
    std::vector<Types::GridBox>::iterator GetActorGrid(std::shared_ptr<Actor> target);

private:
    friend class Engine;
};