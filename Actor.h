#pragma once

class Actor
{
public:
    Actor();

public:
    inline const char* GetSprite() { return Sprite; }
    // Component* GetComponentByClass(Component componentClass)
 
public:
    const char* Id = "XXXX-XXXX";
    const char* Sprite = "A";

    // list<Components> components //TODO all actions like attack can walk and stuff be base in component
};