#pragma once

#include "Types.h"
#include "Character.h"
#include "Utils.h"
#include "SpecialAbility.h"

#include <memory>
#include <list>

class ConstructorHelper
{
public:
    static inline std::shared_ptr<Character> MakeCharacter(int classIndex, float health, float baseDamage, const char *id, const char *sprite, const char *team)
    {
        Types::CharacterClassType CharacterClassType = (Types::CharacterClassType)classIndex;
        Types::CharacterClass characterClass = ConstructorHelper::MakeCharacterClass(CharacterClassType);
        std::list<std::shared_ptr<SpecialAbility>> Skills = ConstructorHelper::MakeCharacterSkills(CharacterClassType);

        auto newCharacter = std::make_shared<Character>(characterClass);
        newCharacter->MaxHealth = characterClass.Health;
        newCharacter->Health = characterClass.Health;
        newCharacter->BaseDamage = characterClass.BaseDamage;
        newCharacter->DamageMultiplier = characterClass.DamageMultiplier;
        newCharacter->Id = id;
        newCharacter->Sprite = sprite;
        newCharacter->Team = team;
        newCharacter->SetSkills(Skills);
        return newCharacter;
    };

    static inline Types::CharacterClass MakeCharacterClass(Types::CharacterClassType characterClassType)
    {
        auto characterClass = Types::CharacterClass{};

        switch (characterClassType)
        {
        case Types::CharacterClassType::Paladin:
            characterClass.Health = 110;
            characterClass.BaseDamage = 20;
            characterClass.DamageMultiplier = Utils::GetRandomFloat(1.2f, 1.5f);
            characterClass.AttackMessage = "In the name of my deity, I strike at this foe with holy power!";
            characterClass.OnMissAttackMessage = "Missed! I will not be deterred, I will strike again with all my might in the name of righteousness!";
            characterClass.OnMDodgeMessage = "With my training and faith, I have dodged the enemy's strike, I will strike back with righteousness.";
            characterClass.OnKillEnemyMessage = "With my training, faith, and righteousness, I have defeated this enemy and protected the innocent.";
            characterClass.OnGetDamageMessage = "I've taken damage, but I will not be defeated. I will continue to fight with all my might in the name of righteousness.";
            characterClass.OnDyingMessage = "I may be dying, but I die in the service of righteousness. My spirit will live on in the causes for which I fought.";
            characterClass.OnWinMessage = "Victory is mine, but the fight for justice continues. I will remain vigilant and continue to serve in the name of righteousness.";
            characterClass.OnCantMoveEffectMessage = "I may be immobile, but my faith in my god will guide my allies to victory.";
            characterClass.OnCantAttackEffectMessage = "I am stunned and unable to attack, my faith in my deity is the only thing that keeps me going.";
            characterClass.probabilityToUseSkill = 30;
            characterClass.AttackActMessage = "%s attacks with holy power against %s!";
            characterClass.probabilityToDodge = 38;

            characterClass.characterAttackEffectsConfig = {
                Types::CharacterAttackEffectsConfig{
                    Types::StatusEffectTypes::Burn,
                    10,
                },
                Types::CharacterAttackEffectsConfig{
                    Types::StatusEffectTypes::KnockDown,
                    20,
                },
                Types::CharacterAttackEffectsConfig{
                    Types::StatusEffectTypes::Stun,
                    25,
                },
            };
            break;
        case Types::CharacterClassType::Warrior:
            characterClass.Health = 130;
            characterClass.BaseDamage = 32;
            characterClass.DamageMultiplier = Utils::GetRandomFloat(1.0f, 1.2f);
            characterClass.AttackMessage = "With all my might, I strike at this enemy!";
            characterClass.OnMissAttackMessage = "I'll not be denied, that was just a scratch, next one will be fatal!";
            characterClass.OnMDodgeMessage = "I've dodged the enemy's strike, now it's my turn to strike back with all my strength.";
            characterClass.OnKillEnemyMessage = "With my training and determination, I've defeated this enemy and emerged victorious.";
            characterClass.OnGetDamageMessage = "I've taken a hit, but it's just a scratch. I'll keep fighting with all my strength.";
            characterClass.OnDyingMessage = "I may be dying, but I die with honor, knowing that I have fought until my last breath.";
            characterClass.OnWinMessage = "Victory is mine, but the battle never ends. I will continue to hone my combat skills and be ready for the next fight.";
            characterClass.OnCantMoveEffectMessage = "I may be down, but I am not out. My determination will see me through this.";
            characterClass.OnCantAttackEffectMessage = "I am stunned and unable to defend myself.";
            characterClass.AttackActMessage = "%s charges towards %s!";
            characterClass.probabilityToUseSkill = 35;
            characterClass.probabilityToDodge = 35;
            characterClass.characterAttackEffectsConfig = {
                Types::CharacterAttackEffectsConfig{
                    Types::StatusEffectTypes::KnockDown,
                    25,
                },
                Types::CharacterAttackEffectsConfig{
                    Types::StatusEffectTypes::Bleed,
                    90,
                },
            };
            break;
        case Types::CharacterClassType::Cleric:
            characterClass.Health = 85;
            characterClass.BaseDamage = 10;
            characterClass.DamageMultiplier = Utils::GetRandomFloat(1.6f, 1.8f);
            characterClass.AttackMessage = "By the power of my deity, I strike at this foe!";
            characterClass.OnMissAttackMessage = "I Missed! I will not falter, I will strike again with the power of my deity on my side.";
            characterClass.OnMDodgeMessage = "With my deity's protection, I have dodged the enemy's strike and I will strike back with the power of my deity.";
            characterClass.OnKillEnemyMessage = "I have struck down the enemy with the power of my deity.";
            characterClass.OnGetDamageMessage = "I have taken damage, but my deity's guidance will protect me and I will continue to fight with their strength.";
            characterClass.OnDyingMessage = "I may be dying, but I die in the service of my deity, my spirit will be reunited with them.";
            characterClass.OnWinMessage = "Victory is mine, but the fight for righteousness continues. I will continue to serve my deity and guide my people towards the path of righteousness.";
            characterClass.OnCantMoveEffectMessage = "My body may be incapacitated, but my spirit remains strong.";
            characterClass.OnCantAttackEffectMessage = "I am stunned and unable to cast spells, I pray for a swift recovery.";
            characterClass.AttackActMessage = "%s casts a spell on %s!";
            characterClass.probabilityToUseSkill = 45;
            characterClass.probabilityToDodge = 39;

            characterClass.characterAttackEffectsConfig = {
                Types::CharacterAttackEffectsConfig{
                    Types::StatusEffectTypes::Stun,
                    30,
                },
                Types::CharacterAttackEffectsConfig{
                    Types::StatusEffectTypes::Burn,
                    38,
                },
            };

            break;
        case Types::CharacterClassType::Archer:
            characterClass.Health = 100;
            characterClass.BaseDamage = 25;
            characterClass.DamageMultiplier = Utils::GetRandomFloat(1.9f, 2.0f);
            characterClass.AttackMessage = "I release my arrow, striking at the target with deadly accuracy!";
            characterClass.OnMissAttackMessage = "I missed, but I'm not done yet, I'll take another shot and make it count.";
            characterClass.OnMDodgeMessage = "With my quick reflexes and training, I've dodged the enemy's strike, now it's my turn to strike back with a well-aimed shot.";
            characterClass.OnKillEnemyMessage = "I have struck down the enemy with a well-aimed shot.";
            characterClass.OnGetDamageMessage = "I have taken damage, but it won't slow me down. I'll keep moving and keep firing until I emerge victorious.";
            characterClass.OnDyingMessage = "I may be dying, but I die with my bow in my hand and the satisfaction of a fight fought.";
            characterClass.OnWinMessage = "Victory is mine, but the battle never ends. I will continue to hone my archery skills and be ready for the next fight.";
            characterClass.OnCantMoveEffectMessage = "I may be grounded, but I still have my bow. I will rain arrows upon our enemies from here.";
            characterClass.OnCantAttackEffectMessage = "I am stunned and unable to attack.";
            characterClass.AttackActMessage = "%s shoots an arrow at %s!";
            characterClass.probabilityToUseSkill = 32;
            characterClass.probabilityToDodge = 45;

            characterClass.characterAttackEffectsConfig = {
                Types::CharacterAttackEffectsConfig{
                    Types::StatusEffectTypes::KnockDown,
                    30,
                },
                Types::CharacterAttackEffectsConfig{
                    Types::StatusEffectTypes::Bleed,
                    38,
                },
            };
            break;

        default:
            break;
        }

        return characterClass;
    }

    static inline std::list<std::shared_ptr<SpecialAbility>> MakeCharacterSkills(Types::CharacterClassType characterClassType)
    {
        auto characterSkill = std::list<std::shared_ptr<SpecialAbility>>();

        switch (characterClassType)
        {
        case Types::CharacterClassType::Paladin:
            characterSkill.push_back(MakeSkills(Types::SpecialAbilityTypes::KnockBack));
            break;
        case Types::CharacterClassType::Warrior:
            characterSkill.push_back(MakeSkills(Types::SpecialAbilityTypes::StrongAttack));
            break;
        case Types::CharacterClassType::Cleric:
            characterSkill.push_back(MakeSkills(Types::SpecialAbilityTypes::Teleport));
            characterSkill.push_back(MakeSkills(Types::SpecialAbilityTypes::Invisibility));
            break;
        case Types::CharacterClassType::Archer:
            characterSkill.push_back(MakeSkills(Types::SpecialAbilityTypes::ThrowRock));
            break;
        }

        return characterSkill;
    }

    static inline std::shared_ptr<SpecialAbility> MakeSkills(Types::SpecialAbilityTypes type)
    {
        auto skill = std::make_shared<SpecialAbility>();
        skill->type = type;
        skill->OnUseSkillMessage = "Take this"; //TODO better ones

        switch (type)
        {
        case Types::SpecialAbilityTypes::KnockBack:
            skill->name = "Knock Back";
            break;
        case Types::SpecialAbilityTypes::StrongAttack:
            skill->name = "Strong Attack";
            break;
        case Types::SpecialAbilityTypes::Teleport:
            skill->bUseSkillOnly = true;
            skill->OnUseSkillMessage = "How about this";
            skill->name = "Teleport";
            break;
        case Types::SpecialAbilityTypes::Invisibility:
            skill->bUseSkillOnly = true;
            skill->name = "Invisibility";
            skill->OnUseSkillMessage = "HA HA HA";
            break;
        case Types::SpecialAbilityTypes::ThrowRock:
            skill->name = "Throw Rock";
            break;
        }

        return skill;
    }

    static inline std::shared_ptr<Types::StatusEffect> MakeStatusEffect(Types::StatusEffectTypes status)
    {
        auto statusEffect = std::make_shared<Types::StatusEffect>(Types::StatusEffect{status, 0, 0, Types::StatusEffectAction::DoNothing, "Nothing?"});

        switch (status)
        {
        case Types::StatusEffectTypes::Bleed:
            statusEffect->duration = 2;
            statusEffect->amount = Utils::GetRandomFloat(2.0, 6.0);
            statusEffect->targetAction = Types::StatusEffectAction::DamageSelf;
            statusEffect->name = "blood loss";
            break;

        case Types::StatusEffectTypes::KnockDown:
            statusEffect->duration = 3;
            statusEffect->amount = 0.0f;
            statusEffect->targetAction = Types::StatusEffectAction::AnyAction;
            statusEffect->name = "knock down";
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