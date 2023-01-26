#include "Character.h"
 
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
	printf("aaaaaaaaa, I got killed \n");
}

float Character::Attack(std::shared_ptr<Character> target) 
{
	//TODO add miss chance
    float damage = BaseDamage * DamageMultiplier;
	target->TakeDamage(damage);
	return damage;
}

Types::ActionType Character::GetActionWhenNearEnemy()
{
	//TODO
	return Types::ActionType::Attack;
}
