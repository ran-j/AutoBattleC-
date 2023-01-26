#pragma once
#include "Grid.h"
#include "Character.h"
#include "Types.h"
#include <memory>

class Character
{
public:
    Character(Types::CharacterClass charcaterClass);
    ~Character();

    
    float Health;
    float BaseDamage;
    float DamageMultiplier;
    //public GridBox currentBox;
    int PlayerIndex;
    //public Character Target{ get; set; }

    std::shared_ptr<Character> target;

    bool IsDead;
    char Icon;

    Types::GridBox currentBox;

    bool TakeDamage(float amount);

    int getIndex(std::vector<Types::GridBox*> v, int index);

    void Die();

    void WalkTo(bool CanWalk);

    bool StartTurn(Grid* battlefield);

    bool CheckCloseTargets(Grid* battlefield);

    void Attack(std::shared_ptr<Character> target);


};

