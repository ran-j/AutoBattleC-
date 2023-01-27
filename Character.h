#pragma once

#include "Actor.h"
#include "Types.h"

#include <memory>
#include <list>

class Character : public Actor
{
public:
    Character(Types::CharacterClass charcaterClass);
    ~Character();

    float Health;
    float MaxHealth;
    float BaseDamage;
    float DamageMultiplier;
    const char *Team;

public:
    //Character die function
    void Die();
    //Take damage from other character
    bool TakeDamage(float amount);    
    //Heal character
    void Heal(float amount);
    //Check if character is dead
    inline bool IsDead() { return bIsDead; }
    //TODO remove this
    Types::ActionType GetActionWhenNearEnemy();
    //Attack other character
    float Attack(std::shared_ptr<Character> target);
    //Check if character has any effect or condition that prevents him from moving
    bool CanMove();
    //Check if character has any effect or condition that prevents him from attacking
    bool CanAttack();

    // Applies negative and positive status effects like heal or bleed
    std::list<const char *> ProcessStatusEffects();
    // Decrease one turn from status effects
    inline void DecreaseStatusEffects()
    {
        if (IsDead())
        {
            return;
        }
        auto it = statusEffects.begin();
        while (it != statusEffects.end())
        {
            Types::StatusEffect *currentEffect = (*it);
            currentEffect->amount--;
            if (currentEffect->amount <= 0)
            {
                it = statusEffects.erase(it);
            }
        }
    }  
    // Apply effect on this character
    inline void ApplyEffect(Types::StatusEffect *effect)
    {
        if (IsDead())
        {
            return;
        }
        //TODO effects can't be added more than once;
        statusEffects.push_back(effect);
    }

private:
    bool bIsDead = false;
    std::list<Types::StatusEffect *> statusEffects;
};
