#include "GameManager.h"
#include "Actor/BulletSpawner.h"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager()
{
	instance = this;


	levels.emplace_back(new StartLevel);
	levels.emplace_back(new GameLevel);
	levels.emplace_back(new EndLevel);

	//SetNewLevel(new StartLevel);
	//SetNewLevel(new GameLevel);
	//SetNewLevel(new );
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
	
	int stateIndex = (int)state;
	int nextState = (int)state + 1;
	state = (State)nextState;

	mainLevel = levels[static_cast<int>(state)];
	
}

void GameManager::EndGame()
{
	system("cls");

	int stateIndex = (int)state;
	int nextState = (int)state + 1;
	state = (State)nextState;

	mainLevel = levels[static_cast<int>(state)];
}

void GameManager::Restart()
{
	//BulletSpawner::Get().ClearPointerListOnly();
	Engine::SetNewLevel(new GameLevel());
	state = (State)1;
	//mainLevel = nextLevel;
}

GameManager& GameManager::Get()
{
	return *instance;
}