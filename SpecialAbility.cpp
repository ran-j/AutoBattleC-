#include "SpecialAbility.h"
#include "ConstructorHelper.h"
#include "Engine.h"

SpecialAbility::SpecialAbility()
{
}

void SpecialAbility::Use(Character *owner, std::shared_ptr<Character> target)
{
    if (type == Types::SpecialAbilityTypes::KnockBack)
    {
        Engine::DrawText(">%s %s", owner->Id, OnUseSkillMessage);

        int currentActorIndex = target->GetActorLocation();
        target->MoveToIndex(currentActorIndex + 1);

        Engine::DrawText("%s use %s on %s", owner->Id, name, target->Id);
    }
}