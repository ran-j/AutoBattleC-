#pragma once

#include <list>
#include <iostream>
#include <map>
#include <list>

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

	std::shared_ptr<Character> CreateCharacter(int classIndex, float health, float baseDamage, const char* id, const char* sprite, const char *team);
	std::shared_ptr<Character> FindCharacterWithDifferentTags(const char *team);
	
	void HandleCombat(std::shared_ptr<Character> attacker, std::shared_ptr<Character> target);
	
private:
	Engine* engine;

	std::shared_ptr<Character> PlayerCharacter;

	std::map<std::shared_ptr<Character>, std::shared_ptr<Character>> CharacterAndTargets;
	list<std::shared_ptr<Character>> TurnQueue;

	int currentTurn = 0;
};


