#pragma once

#include "Actor.h"
#include "Grid.h"
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

    void Attack(std::shared_ptr<Character> target);

    inline bool IsDead() { return bIsDead; }

private:
    bool bIsDead;

};

