#include "GameManager.h"
#include "Actor/BulletSpawner.h"

#include <iostream>

GameManager* GameManager::instance = nullptr;

GameManager::GameManager()
{
	instance = this;


	levels.emplace_back(new StartLevel);
	levels.emplace_back(new GameLevel);
	levels.emplace_back(new EndLevel);

	state = State::GamePlay;

	mainLevel = levels[0];

}

GameManager::~GameManager()
{
	mainLevel = nullptr;

	for (Level*& level : levels)
	{
		delete level;
		level = nullptr;
	}

	levels.clear();

}

void GameManager::StartGame()
{
	system("cls");
	isPlayGame = true;

	int stateIndex = (int)state;
	int nextState = (int)state + 1;
	state = (State)nextState;

	mainLevel = levels[static_cast<int>(state)];
	
}

void GameManager::EndGame()
{
	system("cls");

	isPlayGame = false;

	int stateIndex = (int)state;
	int nextState = (int)state + 1;
	state = (State)nextState;

	mainLevel = levels[static_cast<int>(state)];
}


void GameManager::Restart()
{
	Engine::SetNewLevel(new GameLevel());
	state = (State)1;
	isPlayGame = true;
}

GameManager& GameManager::Get()
{
	if (!instance)
	{
		std::cout << "Error : GameManager::Get(). instance is null.";
		__debugbreak;
	}

	return *instance;
}

void GameManager::ShowScore()
{
	sprintf_s(scoreString, 128, "Score: %d", score);
	Renderer::Get().Submit(
		scoreString,
		Vector2(0, Engine::Get().GetHeight() - 1)
	);
}

void GameManager::ShowEndScore()
{
	sprintf_s(scoreString, 128, "Score: %d", score);
	Renderer::Get().Submit(
		scoreString,
		Vector2(Engine::Get().GetWidth() / 2, Engine::Get().GetHeight() / 3 + 3)
	);
}

void GameManager::Score(float deltaTime)
{
	if(isPlayGame){
		scoreAccumulator += deltaTime;

		if (scoreAccumulator >= 1.0f)
		{
			score += 1;
			scoreAccumulator = 0.0f;
		}
	}
}