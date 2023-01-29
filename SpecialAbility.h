//This class represents all special abilities
#pragma once

#include "Types.h"
#include "Character.h"

#include <memory>

class SpecialAbility
{
public:
    SpecialAbility();

public:
    Types::SpecialAbilityTypes type;
    const char *name;
    const char *OnUseSkillMessage;
    // tell if this skill should replace all owner actions
    bool bUseSkillOnly = false;

public:
    // Use skill
    void Use(Character *owner, std::shared_ptr<Character> target);
    // tell if this skill should replace all owner actions
    inline bool ShouldUseSkillOnly()
    {
        return bUseSkillOnly;
    }
};
