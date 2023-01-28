#include "Character.h"
#include "Utils.h"
#include "ConstructorHelper.h"
#include "Engine.h"

#include <string>

using namespace std;
Character::Character(Types::CharacterClass characterClass)
{
	statusEffects = list<std::shared_ptr<Types::StatusEffect>>();
	mCharacterClass = characterClass;
}

Character::~Character()
{
	statusEffects.clear();
}

bool Character::TakeDamage(float amount)
{
	// TODO add miss chance base on attributes
	if ((Health -= amount) <= 0)
	{
		bIsDead = true;
		Die();
		return true;
	}
	Engine::DrawText(">%s: %s \n", this->Id, mCharacterClass.OnGetDamageMessage);
	return true;
}

void Character::Heal(float amount)
{
	if ((Health += amount) >= MaxHealth)
	{
		Health = MaxHealth;
	}
}

void Character::Die()
{
	statusEffects.clear();
	bIsDead = true;
	Engine::DrawText(">%s: %s \n", this->Id, mCharacterClass.OnDyingMessage);
}

float Character::Attack(std::shared_ptr<Character> target)
{
	float dice = Utils::RollD4();
	float damage = BaseDamage * DamageMultiplier * dice;

	bool didTakeDamage = !target->TakeDamage(damage);

	if (didTakeDamage)
	{
		return 0.0f;
	}

	if (!target->IsDead())
	{
		for (auto it = mCharacterClass.characterAttackEffectsConfig.begin(); it != mCharacterClass.characterAttackEffectsConfig.end(); ++it)
		{
			if (Utils::GetRandomBoolWithProbability((*it).probability))
			{
				auto newEffect = ConstructorHelper::CreateStatusEffect((*it).type);
				Engine::DrawText("%s manage do apply %s on %s", this->Id, newEffect->name, target->Id);
				target->ApplyEffect(newEffect);
			}

		}
	}

	return damage;
}

void Character::ProcessStatusEffects()
{
	if (IsDead())
	{
		return;
	}
	for (auto it = statusEffects.begin(); it != statusEffects.end(); ++it)
	{
		std::shared_ptr<Types::StatusEffect> currentEffect = (*it);
		switch (currentEffect->targetAction)
		{
		case Types::StatusEffectAction::DamageSelf:
			TakeDamage(currentEffect->amount);
			Engine::DrawText("%s suffered %f of damage because of %s effect", this->Id, currentEffect->amount, currentEffect->name);
			break;
		case Types::StatusEffectAction::HealSelf:
			Heal(currentEffect->amount);
			Engine::DrawText("%s heals %f percent of life because of %s effect", this->Id, currentEffect->amount, currentEffect->name);
			break;
		}
	}
}

bool Character::CanMoveAndPrintMessageIfCant()
{
	if (IsDead())
	{
		return false;
	}
	std::list<std::shared_ptr<Types::StatusEffect>> blockMovementEffectList = GetEffectByAction(Types::StatusEffectAction::AnyMove);
	if (blockMovementEffectList.size() > 0)
	{
		auto first = blockMovementEffectList.begin(); // for this man we can inform only one
		Engine::DrawText("%s can't move because of effect(s) %s", this->Id, (*first)->name);
		Engine::DrawText(">%s: %s \n", this->Id, mCharacterClass.OnCantMoveEffectMessage);
		return false;
	}
	return true;
}

bool Character::CanAttackAndPrintMessageIfCant()
{
	if (IsDead())
	{
		return false;
	}
	std::list<std::shared_ptr<Types::StatusEffect>> blockMovementEffectList = GetEffectByAction(Types::StatusEffectAction::AnyAttack);
	if (blockMovementEffectList.size() > 0)
	{
		auto first = blockMovementEffectList.begin(); // for this man we can inform only one
		Engine::DrawText("%s can't attack because of effect(s) %s", this->Id, (*first)->name);
		Engine::DrawText(">%s: %s \n", this->Id, mCharacterClass.OnCantAttackEffectMessage);
		return false;
	}
	return true;
}

bool Character::CanPlayTurnAndPrintMessageIfCant()
{
	std::list<std::shared_ptr<Types::StatusEffect>> blockAnyActionEffect = GetEffectByAction(Types::StatusEffectAction::AnyAction);

	if (blockAnyActionEffect.size() > 0)
	{
		std::string effectNames;
		for (auto it = blockAnyActionEffect.begin(); it != blockAnyActionEffect.end(); ++it)
		{
			effectNames += (*it)->name;
			effectNames += ", ";
		}
		effectNames = effectNames.substr(0, effectNames.length() - 2); // remove the last ", " from the effectNames string
		Engine::DrawText("%s can't do anything because of effect(s) %s", this->Id, effectNames.c_str());
		return false;
	}
	return true;
}

std::list<std::shared_ptr<Types::StatusEffect>> Character::GetEffectByAction(Types::StatusEffectAction actionType)
{
	auto foundedEffects = std::list<std::shared_ptr<Types::StatusEffect>>();
	for (auto it = statusEffects.begin(); it != statusEffects.end(); ++it)
	{
		std::shared_ptr<Types::StatusEffect> currentEffect = (*it);
		if (currentEffect->targetAction == actionType)
		{
			foundedEffects.push_back(currentEffect);
		}
	}
	return foundedEffects;
}

void Character::PlayTurn(bool isNearTarget, std::shared_ptr<Character> target, std::function<void()> moveToTargetLocationFunc)
{
	if (IsDead())
	{
		Die();
		return;
	}

	if (!CanPlayTurnAndPrintMessageIfCant())
	{
		Engine::DrawText(">%s: %s \n", this->Id, mCharacterClass.OnCantAttackEffectMessage);
		return;
	}

	if (isNearTarget)
	{
		// TODO decide if should attack or use skill
		if (CanAttackAndPrintMessageIfCant())
		{
			// Engine::DrawText("%s launch a attack in %s", this->Id, target->Id);
			Engine::DrawText(">%s: %s \n", this->Id, mCharacterClass.AttackMessage);
			Engine::DrawText(mCharacterClass.AttackActMessage, this->Id, target->Id);

			float damage = Attack(target);
			if (damage == 0)
			{
				Engine::DrawText("%s miss the attack on %s", this->Id, target->Id);
				Engine::DrawText(">%s: %s \n", this->Id, mCharacterClass.OnMissAttackMessage);
			}
			else
			{
				Engine::DrawText("%s dealt %f damage points to %s", this->Id, damage, target->Id);
				if (target->IsDead())
				{
					Engine::DrawText("\n *** %s killed %s *** \n", this->Id, target->Id);
					Engine::DrawText(mCharacterClass.OnKillEnemyMessage, this->Id, target->Id);
					return;
				}
			}
		}
	}
	else
	{
		if (CanMoveAndPrintMessageIfCant())
		{
			moveToTargetLocationFunc();
			Engine::DrawText("%s move to %s direction", this->Id, target->Id);
		}
	}
}

void Character::WinGame()
{
	Engine::DrawText(">%s: %s \n", this->Id, mCharacterClass.OnWinMessage);
}