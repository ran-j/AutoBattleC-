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

    bool TakeDamage(float amount);

    void Die();

    float Attack(std::shared_ptr<Character> target);
    Types::ActionType GetActionWhenNearEnemy();
    inline bool IsDead() { return bIsDead; }

private:
    bool bIsDead = false;

};

