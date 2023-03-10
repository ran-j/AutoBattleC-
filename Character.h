#pragma once

#include "Actor.h"
#include "Types.h"

#include <memory>
#include <list>
#include <functional>

class SpecialAbility;
class Character : public Actor
{
public:
    Character(Types::CharacterClass characterClass);
    ~Character();

    float Health;
    float MaxHealth;
    float BaseDamage;
    float DamageMultiplier;
    const char *Team;
    // add shield
    // add dex to dodge attack

public:
    // Character die function
    void Die();
    // Tells that character win the game
    void WinGame();
    // Take damage from other character and returns if hit or not
    bool TakeDamage(float amount);
    // Heal character
    void Heal(float amount);
    // Check if character is dead
    inline bool IsDead() { return bIsDead; }
    // Attack other character
    float Attack(std::shared_ptr<Character> target);
    // Do action in one turn
    void PlayTurn(std::shared_ptr<Character> target);

public:
    // Applies negative and positive status effects like heal or bleed
    void ProcessStatusEffects();
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
            std::shared_ptr<Types::StatusEffect> currentEffect = (*it);
            currentEffect->duration -= 1;
            if (currentEffect->duration + 1 <= 0) // :) +1 to jump the current step on this turn # prevent for loss duration without apply effect
            {
                it = statusEffects.erase(it);
            }
            else
            {
                it++;
            }
        }
    }
    // Apply effect on this character
    inline void ApplyEffect(std::shared_ptr<Types::StatusEffect> effect)
    {
        if (IsDead())
        {
            return;
        }
        // TODO effects can't be added more than once;
        statusEffects.push_back(effect);
    }
    // Get a list if exist of character effects active
    std::list<std::shared_ptr<Types::StatusEffect>> GetEffectByAction(Types::StatusEffectAction actionType);

public:
    inline void SetSkills(std::list<std::shared_ptr<SpecialAbility>> skills)
    {
        Skills = skills;
    }

private:
    bool bIsDead = false;
    std::list<std::shared_ptr<Types::StatusEffect>> statusEffects;
    std::list<std::shared_ptr<SpecialAbility>> Skills;
    Types::CharacterClass mCharacterClass;

protected:
    // Check if character has any effect or condition that prevents him from moving
    bool CanMoveAndPrintMessageIfCant();
    // Check if character has any effect or condition that prevents him from attacking
    bool CanAttackAndPrintMessageIfCant();
    // Check if character can play the current turn
    bool CanPlayTurnAndPrintMessageIfCant();
    // Return one skill if character have one and should use one
    std::shared_ptr<SpecialAbility> GetSkillToUseIfCan();
};