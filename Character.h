#pragma once

#include "Actor.h" 
#include "Types.h"

#include <memory>

class Character: public Actor
{
public:
    Character(Types::CharacterClass charcaterClass);
    ~Character();

    float Health;
    float BaseDamage;
    float DamageMultiplier;
    const char* Team;

public:
    void Die();
    bool TakeDamage(float amount);
    inline bool IsDead() { return bIsDead; }
    Types::ActionType GetActionWhenNearEnemy();
    float Attack(std::shared_ptr<Character> target);

private:
    bool bIsDead = false;

};

