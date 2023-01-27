#include "Character.h"
#include "Utils.h"
 
using namespace std;
Character::Character(Types::CharacterClass charcaterClass)
{
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

void Character::Die() 
{
	printf("%s : aaaaaaaaa, I got killed \n", Id);
}

float Character::Attack(std::shared_ptr<Character> target) 
{
	//TODO add miss chance
	float dice = Utils::RollD4();
    float damage = BaseDamage * DamageMultiplier * dice;
	target->TakeDamage(damage);
	return damage;
}

Types::ActionType Character::GetActionWhenNearEnemy()
{
	//TODO
	return Types::ActionType::Attack;
}
