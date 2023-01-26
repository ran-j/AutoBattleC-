#pragma once

#include "Types.h"
#include "Grid.h"

#include <map>
#include <vector>
#include <iostream>

// limitation the render queue is sync if you try to run async you will lose data

class Actor;
class Grid;

// Char Turn Engine
class Engine
{
public:
    Engine();
    // Init game engine
    void Init(int lines, int Columns);
    // Will draw the grid with actors in place
    void Draw();
    // Add actor to render queue
    void SpawnActor(std::shared_ptr<Actor> target);
    // Tells if should continue in game loop
    inline bool ShouldQuit() { return bShouldQuit; }
    // Return the world tiles size
    inline int GetWorldSize() { return static_cast<int>(grid->grids.size()); }
    // Return Actor index in world tiles
    int GetActorLocation(std::shared_ptr<Actor> target);
    // Move Actor to a target location
    void MoveActorToTarget(std::shared_ptr<Actor> actor, std::shared_ptr<Actor> target);
    // Check if a actor is close to another target
    bool IsCloseToTarget(std::shared_ptr<Actor>actor, std::shared_ptr<Actor> target);
    // Returns actor current grid
    std::vector<Types::GridBox>::iterator GetActorGrid(std::shared_ptr<Actor> target);
    // Clear user viewport
    void ClearCanvas();
    // Draw user text on viewport
    void DrawText(const char *format, ...);
    // Tells engine to stop render
    inline void Stop() { bShouldQuit = true; };
    //Wait to user input
    inline void WaitInput()
    {
#ifdef __linux__
        system("read");
#elif _WIN32
        system("pause");
#endif
    };

    int GetRandomInt(int min, int max);
    double DistanceTo(double x1, double y1, double x2, double y2);

private:
    // Set Actor Index
    void SetActorIndex(std::shared_ptr<Actor> target, int index);

private:
    // list to actor to be draw
    std::map<int, std::shared_ptr<Actor>> Actors;      // should I use unordered_map?
    //Track of actors position in world
    std::map<const char *, int> ActorsWorldPositions; // should I use unordered_map?
    // world grid
    Grid *grid;

    bool bShouldQuit = false;
    bool bHasChanges = false; // in future convert this to int

    int mLines = 0;
    int mColumns = 0;
};