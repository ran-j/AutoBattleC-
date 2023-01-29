#include "SpecialAbility.h"
#include "ConstructorHelper.h"
#include "Engine.h"

SpecialAbility::SpecialAbility()
{
}

void SpecialAbility::Use(Character *owner, std::shared_ptr<Character> target)
{
    Engine::DrawText(">%s %s", owner->Id, OnUseSkillMessage);
    Engine::DrawText("%s use %s on %s", owner->Id, name, target->Id);
    if (type == Types::SpecialAbilityTypes::KnockBack)
    {
        int currentActorIndex = target->GetActorLocation();
        target->MoveToIndex(currentActorIndex + 1);
    }
    else if (type == Types::SpecialAbilityTypes::StrongAttack)
    {
        float cache = owner->DamageMultiplier;
        owner->DamageMultiplier = owner->DamageMultiplier * 2;
        owner->Attack(target);
        owner->DamageMultiplier = cache;         
    } else if (type == Types::SpecialAbilityTypes::Teleport)
    {
        int currentActorIndex = target->GetActorLocation();
        target->MoveToIndex(currentActorIndex + 3); //TODO random number with grid size
    }
    else if (type == Types::SpecialAbilityTypes::Invisibility)
    {
        //TODO
    }
    else if (type == Types::SpecialAbilityTypes::ThrowRock)
    {
        bool isInRange = owner->IsCloseToTarget(target, 2);
        if (isInRange) 
        {
            owner->Attack(target);
        } else 
        {
            Engine::DrawText("%s is out of range", target->Id);
        }
    }

}