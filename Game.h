//This class know all game logic like how many player will play and send then to render

#pragma once

#include <list>
#include <iostream>
#include <map>
#include <list>

using namespace std;

class Engine;
class Character;

class Game
{
public:
	Game();
	void Init();

private:
	//Prepare the battlefield and start the game
	void SetUpGame();
	//Do players actions in turn
	void StartTurn();
	//Handle the end of turn event
	void HandleTurn();
	//Handle combat from characters
	void HandleCombat(std::shared_ptr<Character> attacker, std::shared_ptr<Character> target);

private: //Search operation in players list
	//Find Characters from different teams
	std::shared_ptr<Character> FindCharacterWithDifferentTags(const char *team);
	//Find Character with same team 
	std::shared_ptr<Character> FindCharacterWithSameTags(const char *team);	

private:
	Engine* engine;

	std::shared_ptr<Character> PlayerCharacter;

	std::map<std::shared_ptr<Character>, std::shared_ptr<Character>> CharacterAndTargets;
	list<std::shared_ptr<Character>> PlayersQueue;

	int currentTurn = 0;
};


