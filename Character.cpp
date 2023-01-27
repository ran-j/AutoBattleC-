#include "Character.h"
#include "Utils.h"
#include "ConstructorHelper.h"

using namespace std;
Character::Character(Types::CharacterClass charcaterClass)
{
	statusEffects = list<Types::StatusEffect *>();
}

Character::~Character()
{
}

bool Character::TakeDamage(float amount)
{
	if ((Health -= amount) <= 0)
	{
		bIsDead = true;
		Die();
		return true;
	}
	return false;
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
	printf("%s : aaaaaaaaa, I got killed \n", Id);
}

float Character::Attack(std::shared_ptr<Character> target)
{
	// TODO add miss chance
	float dice = Utils::RollD4();
	float damage = BaseDamage * DamageMultiplier * dice;

	target->TakeDamage(damage);

	// 40% to apply bleed
	if(Utils::GetRandomBoolWithProbability(40))
	{
		auto bleedEffect = ConstructorHelper::CreateStatusEffect(Types::Bleed);
		printf("Applying bleed effect on target \n");
		target->ApplyEffect(bleedEffect);
	}

	return damage;
}

Types::ActionType Character::GetActionWhenNearEnemy()
{
	// TODO
	return Types::ActionType::Attack;
}

std::list<const char *> Character::ProcessStatusEffects()
{
	auto textEffects = list<const char *>();
	if (bIsDead)
	{
		return textEffects;
	}

	for (auto it = statusEffects.begin(); it != statusEffects.end(); ++it)
	{
		Types::StatusEffect *currentEffect = (*it);
		switch (currentEffect->targetAction)
		{
		case Types::ActionType::Attack:
			TakeDamage(currentEffect->amount);

			//Should I use stringstream ?
			char buffer1[100];
			sprintf_s(buffer1, "Suffered %f of damage because of %s effect", currentEffect->amount, currentEffect->name);

			textEffects.push_back(buffer1);
			break;
		case Types::ActionType::Heal:

			char buffer2[100];
			sprintf_s(buffer2, "Heals %f of life because of %s effect", currentEffect->amount, currentEffect->name);
			textEffects.push_back(buffer2);

			Heal(currentEffect->amount);
			break;
		}
	}

	return textEffects;
}

bool Character::CanMove()
{
	return true;
}

bool CanAttack()
{
	return true;
}