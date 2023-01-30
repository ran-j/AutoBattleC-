//This class represents all Object that can be render in game

#pragma once

#include "WorldMatrix.h"

#include <memory>

class Actor : public std::enable_shared_from_this<Actor>
{
public:
    Actor();

public:
    inline const char* GetSprite() { return Sprite; }

public: //Movement functions

    inline int GetActorLocation()
    {
        return this->worldMatrix->GetActorLocation(shared_from_this());
    }

    inline void MoveToTargetLocation(std::shared_ptr<Actor> target)
    {
        this->worldMatrix->MoveActorToTarget(shared_from_this(), target);
    }

    inline bool IsCloseToTarget(std::shared_ptr<Actor> target, double distance = 1)
    {
        return this->worldMatrix->IsCloseToTarget(shared_from_this(), target, distance);
    }

    inline void MoveToIndex(int index)
    {
        this->worldMatrix->MoveActorToIndex(shared_from_this(), index);
    }

private:
    std::shared_ptr<WorldMatrix> worldMatrix;
 
public:
    const char* Id = "XXXX-XXXX";
    const char* Sprite = "A"; 
    bool bIsHiddenInGame = false;

private:
    friend class Engine;
};