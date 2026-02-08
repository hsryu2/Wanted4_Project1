#pragma once
#include "Engine/Engine.h"
#include "Level/GameLevel.h"
#include "Level/StartLevel.h"
#include "Level/EndLevel.h"

using namespace Wanted;

enum class State
{
	GamePlay = 0,
	GameStart = 1,
	Restart = 2,
	Length
};

class GameManager : public Engine
{
public:
	GameManager();
	~GameManager();

	void StartGame();
	void EndGame();

	void Restart();

	static GameManager& Get();
private:
	std::vector<Level*> levels;

	State state = State::GamePlay;

	static GameManager* instance;
};

