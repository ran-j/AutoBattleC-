#pragma once
class Types
{
public:

    //TODO better names for this Struct
    struct GridBox
    {
        int xIndex;
        int yIndex;
        bool ocupied;
        int Index;

        GridBox(int x, int y, bool bOccupied, int index)
        {
            xIndex = x;
            yIndex = y;
            ocupied = bOccupied;
            Index = index;
        }
    };

    enum CharacterClass
    {
        Paladin = 1,
        Warrior = 2,
        Cleric = 3,
        Archer = 4
    };

    enum ActionType
    {
        Any = 0,
        Heal = 1,
        Attack = 2,
        UseSkill = 3,
        Move = 5,
        
    };

    enum StatusEffectTypes
    {
        //Lose health over 2 turns
        Bleed = 1,
        //Can't do nothing for 3 turns
        KnockBack = 2,
        //Heal over 2 turns
        Cure = 3,
        //Can't do nothing for one turn
        Stun = 4,
        //Lose health by burn over 3 turns
        Burn = 5,
    };

    enum StatusEffectAction
    {
        DamageSelf = 1,
        HealSelf = 2,
        AnyMove = 3,
        AnyAttack = 4,
        AnyAction = 5,
        DoNothing = 6,
    };

    struct StatusEffect
    {
        StatusEffectTypes type;
        StatusEffectAction targetAction;
        int duration;
        float amount;
        const char * name;

        StatusEffect(StatusEffectTypes effect, int duration, float amountData, StatusEffectAction action, const char * effectName)
        {
            type = effect;
            duration = duration;
            amount = amountData;
            targetAction = action;
            name = effectName;
        }
    };

};

