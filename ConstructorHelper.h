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
        Types::CharacterClassType CharacterClassType = (Types::CharacterClassType)classIndex;

        
        auto newCharacter = std::make_shared<Character>(CharacterClassType);
        newCharacter->MaxHealth = health;
        newCharacter->Health = health;
        newCharacter->BaseDamage = baseDamage;
        newCharacter->DamageMultiplier = Utils::GetRandomFloat(0.2, 1.0); // TODO class influence in life and damage
        newCharacter->Id = id;
        newCharacter->Sprite = sprite;
        newCharacter->Team = team;
        return newCharacter;
    };

    static inline Types::CharacterClass GetCharacterClass(Types::CharacterClassType characterClassType)
    {
        auto characterClass = Types::CharacterClass{};

        switch (characterClassType)
        {
        case Types::CharacterClassType::Paladin:
            characterClass.Health = 110;
            characterClass.BaseDamage = 20;
            characterClass.DamageMultiplier = 1.5;
            characterClass.AttackMessage = "In the name of my deity, I strike at this foe with holy power!";
            characterClass.OnMissAttackMessage = "Missed! I will not be deterred, I will strike again with all my might in the name of righteousness!";
            characterClass.OnMDodgeMessage = "With my training and faith, I have dodged the enemy's strike, I will strike back with righteousness.";
            characterClass.OnKillEnemyMessage = "With my training, faith, and righteousness, I have defeated this enemy and protected the innocent.";
            characterClass.OnGetDamageMessage = "I've taken damage, but I will not be defeated. I will continue to fight with all my might in the name of righteousness.";
            characterClass.OnDyingMessage = "I may be dying, but I die in the service of righteousness. My spirit will live on in the causes for which I fought.";
            characterClass.OnWinMessage = "Victory is mine, but the fight for justice continues. I will remain vigilant and continue to serve in the name of righteousness.";
            characterClass.OnCantMoveEffectMessage = "I may be immobile, but my faith in my god will guide my allies to victory.";
            characterClass.OnCantAttackEffectMessage = "I am stunned and unable to attack, my faith in my deity is the only thing that keeps me going.";
            break;
        case Types::CharacterClassType::Warrior:
            characterClass.Health = 130;
            characterClass.BaseDamage = 30;
            characterClass.DamageMultiplier = 1.2;
            characterClass.AttackMessage = "With all my might, I strike at this enemy!";
            characterClass.OnMissAttackMessage = "I'll not be denied, that was just a scratch, next one will be fatal!";
            characterClass.OnMDodgeMessage = "I've dodged the enemy's strike, now it's my turn to strike back with all my strength.";
            characterClass.OnKillEnemyMessage = "With my training and determination, I've defeated this enemy and emerged victorious.";
            characterClass.OnGetDamageMessage = "I've taken a hit, but it's just a scratch. I'll keep fighting with all my strength.";
            characterClass.OnDyingMessage = "I may be dying, but I die with honor, knowing that I have fought until my last breath.";
            characterClass.OnWinMessage = "Victory is mine, but the battle never ends. I will continue to hone my combat skills and be ready for the next fight.";
            characterClass.OnCantMoveEffectMessage = "I may be down, but I am not out. My determination will see me through this.";
            characterClass.OnCantAttackEffectMessage = "I am stunned and unable to defend myself.";
            break;
        case Types::CharacterClassType::Cleric:
            characterClass.Health = 85;
            characterClass.BaseDamage = 10;
            characterClass.DamageMultiplier = 1.8;
            characterClass.AttackMessage = "By the power of my deity, I strike at this foe!";
            characterClass.OnMissAttackMessage = "I Missed! I will not falter, I will strike again with the power of my deity on my side.";
            characterClass.OnMDodgeMessage = "With my deity's protection, I have dodged the enemy's strike and I will strike back with the power of my deity.";
            characterClass.OnKillEnemyMessage = "I have struck down the enemy with the power of my deity.";
            characterClass.OnGetDamageMessage = "I have taken damage, but my deity's guidance will protect me and I will continue to fight with their strength.";
            characterClass.OnDyingMessage = "I may be dying, but I die in the service of my deity, my spirit will be reunited with them.";
            characterClass.OnWinMessage = "Victory is mine, but the fight for righteousness continues. I will continue to serve my deity and guide my people towards the path of righteousness.";
            characterClass.OnCantMoveEffectMessage = "My body may be incapacitated, but my spirit remains strong.";
            characterClass.OnCantAttackEffectMessage = "I am stunned and unable to cast spells, I pray for a swift recovery.";

            break;
        case Types::CharacterClassType::Archer:
            characterClass.Health = 100;
            characterClass.BaseDamage = 25;
            characterClass.DamageMultiplier = 2.0;
            characterClass.AttackMessage = "I release my arrow, striking at the target with deadly accuracy!";            
            characterClass.OnMissAttackMessage = "I missed, but I'm not done yet, I'll take another shot and make it count.";
            characterClass.OnMDodgeMessage = "With my quick reflexes and training, I've dodged the enemy's strike, now it's my turn to strike back with a well-aimed shot.";
            characterClass.OnKillEnemyMessage = "I have struck down the enemy with a well-aimed shot.";
            characterClass.OnGetDamageMessage = "I have taken damage, but it won't slow me down. I'll keep moving and keep firing until I emerge victorious.";
            characterClass.OnDyingMessage = "I may be dying, but I die with my bow in my hand and the satisfaction of a fight fought.";
            characterClass.OnWinMessage = "Victory is mine, but the battle never ends. I will continue to hone my archery skills and be ready for the next fight.";
            characterClass.OnCantMoveEffectMessage = "I may be grounded, but I still have my bow. I will rain arrows upon our enemies from here.";
            characterClass.OnCantAttackEffectMessage = "I am stunned and unable to attack.";

            break;

        default:
            break;
        }

        return characterClass;
    }

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