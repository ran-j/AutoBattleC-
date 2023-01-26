#pragma once

#include "Types.h"
#include "Grid.h"

#include <map>
#include <vector>

//limitation the render queue is sync if you try to run async you will lose data

class Actor;
class Grid;

//Char Turn Engine
class Engine
{
public:
    Engine();
    //Init game engine
    void Init(int lines, int Columns);    
    //Will draw the grid with actors in place
    void Draw();
    //Add actor to render queue 
    void InsertActor(Actor *target);
    //Tells if should continue in game loop
    inline bool ShouldQuit() { return bShouldQuit; }
    //Return the world tiles size
    inline int GetWorldSize() { return static_cast<int>(grid->grids.size()); }
    //Return Actor index in world tiles
    int GetActorLocation(Actor *target);
    //Move Actor to a target location 
    void MoveActorToTarget(Actor *actor, Actor *target);
    //Check if a actor is close to another target
    bool IsCloseToTarget(Actor *actor, Actor *target);
    //Returns actor current grid
    std::vector<Types::GridBox>::iterator GetActorGrid(Actor *target);

    int GetRandomInt(int min, int max);

private:
    //Set Actor Index 
    void SetActorIndex(Actor *target, int index);

private: 
    //list to actor to be draw
    std::map<int, Actor*> Actors;  //should I use unordered_map?
    std::map<const char *, int> ActorsWorldPositions;  //should I use unordered_map?
    //world
    Grid* grid; 

    bool bShouldQuit = false;
    bool bHasChanges = false; //in future convert this to int

    int mLines = 0;
    int mColumns = 0;
};