#pragma once

#include <list>
#include <iostream>
#include <map>

using namespace std;

class Engine;
class Character;
class BattleField
{
public:

	BattleField();

	void Init();

private:
	void SetUpGame();
	void StartTurn();
	void HandleTurn();

	Character* CreateCharacter(int classIndex, float health, float baseDamage, const char* id, const char* sprite);


	int GetRandomInt(int min, int max);
	
private:
	Engine* engine;

	Character* PlayerCharacter; //TODO unique pointer
	Character* EnemyCharacter; //TODO unique pointer

	std::map<Character *, Character*> CharacterAndTargets;

	bool bPlayerActFirst;
	int currentTurn = 0;
};


