//All logic render are here this is should be the only class that know how to render
//This class should be a singleton
//limitation the render queue is sync if you try to run async you will lose data

#pragma once

#include "Types.h"
#include "Grid.h"

#include <map>
#include <vector>
#include <iostream>
#include <stdarg.h>

class Actor;
class Grid;
class WorldMatrix;

// Char Turn Engine
class Engine
{
public:
    Engine();
    // Init game engine
    void Init(int lines, int Columns);
    // Will draw the grid with actors in place
    void Draw();
    // Draw user text on viewport
    static inline void DrawText(const char *format, ...)
    {
        va_list args;
        va_start(args, format);
        vfprintf(stdout, format, args);
        printf("\n");
        va_end(args);
    }
    // Wait to user input
    static inline void WaitInput()
    {
#ifdef __linux__
        system("read");
#elif _WIN32
        system("pause");
#endif
        printf("\n");
    };

    // Add actor to render queue
    void SpawnActor(std::shared_ptr<Actor> target);
    // Destroy actor to render queue
    void DestroyActor(std::shared_ptr<Actor> target);
    // Tells if should continue in game loop
    inline bool ShouldQuit() { return bShouldQuit; }
    // Clear user viewport
    void ClearViewPort();
    // Tells engine to stop render
    inline void Stop() { bShouldQuit = true; };
    //Get world Matrix to do operation like walk and teleport
    inline std::shared_ptr<WorldMatrix> GetWorldMatrix() { return worldMatrix; }

private:
    bool bShouldQuit = false;
    bool bHasChanges = false; // in future convert this to int

    std::shared_ptr<WorldMatrix> worldMatrix;
};