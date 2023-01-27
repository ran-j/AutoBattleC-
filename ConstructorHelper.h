#pragma once

#include "Types.h"
#include "Character.h"
#include "Utils.h"

#include <memory>

class ConstructorHelper
{
public:
    static inline std::shared_ptr<Character> CreateCharacter(int classIndex, float health, float baseDamage, const char *id, const char *sprite, const char *team)
    {
        Types::CharacterClass characterClass = (Types::CharacterClass)classIndex;
        auto newCharacter = std::make_shared<Character>(characterClass);
        newCharacter->MaxHealth = health;
        newCharacter->Health = health;
        newCharacter->BaseDamage = baseDamage;
        newCharacter->DamageMultiplier = Utils::GetRandomFloat(0.2, 1.0); // TODO class influence in life and damage
        newCharacter->Id = id;
        newCharacter->Sprite = sprite;
        newCharacter->Team = team;
        return newCharacter;
    };

    static inline std::shared_ptr<Types::StatusEffect> CreateStatusEffect(Types::StatusEffectTypes status)
    {
        auto statusEffect = std::make_shared<Types::StatusEffect>(Types::StatusEffect{ status, 0, 0, Types::StatusEffectAction::DoNothing, "Nothing?" });

        switch (status)
        {
        case Types::StatusEffectTypes::Bleed:
            statusEffect->duration = 2;
            statusEffect->amount = Utils::GetRandomFloat(2.0, 6.0);
            statusEffect->targetAction = Types::StatusEffectAction::DamageSelf;
            statusEffect->name = "blood loss";
            break;

        case Types::StatusEffectTypes::KnockBack:
            statusEffect->duration = 3;
            statusEffect->amount = 0.0f;
            statusEffect->targetAction = Types::StatusEffectAction::AnyAction;
            statusEffect->name = "knock back";
            break;

        case Types::StatusEffectTypes::Cure:
            statusEffect->duration = 2;
            statusEffect->amount = 6.0f;
            statusEffect->targetAction = Types::StatusEffectAction::HealSelf;
            statusEffect->name = "magic cure";
            break;

        case Types::StatusEffectTypes::Stun:
            statusEffect->duration = 1;
            statusEffect->amount = 0.0f;
            statusEffect->targetAction = Types::StatusEffectAction::AnyMove;
            statusEffect->name = "stun";
            break;
        case Types::StatusEffectTypes::Burn:
            statusEffect->duration = 3;
            statusEffect->amount = Utils::GetRandomFloat(8.0, 10.0);
            statusEffect->targetAction = Types::StatusEffectAction::DamageSelf;
            statusEffect->name = "burning";
            break;
        }

        return statusEffect;
    }
};