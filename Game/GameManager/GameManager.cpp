#include "GameManager.h"
#include "Actor/BulletSpawner.h"
#include "Actor/Player.h"

#include <iostream>

GameManager* GameManager::instance = nullptr;

GameManager::GameManager()
{
	instance = this;


	levels.emplace_back(new StartLevel);
	levels.emplace_back(new GameLevel);
	levels.emplace_back(new EndLevel);
	levels.emplace_back(new PauseLevel);

	state = State::GamePlay;

	// 초기 화면 : StartLevel = 0
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

// StartGame 호출 시 메인 게임으로 넘어감 GameLevel = 1
void GameManager::StartGame()
{
	system("cls");
	isPlayGame = true;

	int stateIndex = (int)state;
	int nextState = (int)state + 1;
	state = (State)nextState;

	mainLevel = levels[static_cast<int>(state)];
	
}

// 게임 오버
void GameManager::EndGame()
{
	system("cls");

	isPlayGame = false;

	int stateIndex = (int)state;
	int nextState = (int)state + 1;
	state = (State)nextState;

	mainLevel = levels[static_cast<int>(state)];
}

// 재시작
void GameManager::Restart()
{
	score = 0;
	state = State::GameStart;
	isPlayGame = true;

	// 기존에 벡터가 들고 있던 GameLevel Index 메모리 해제.
	if (levels[1] != nullptr)
	{
		delete levels[1];
	}

	// 새로운 레벨 객체 생성 및 벡터 업데이트.
	levels[1] = new GameLevel();

	// 엔진에 새로운 레벨을 세팅.
	Engine::Get().SetNewLevel(levels[1]);
}


void GameManager::PauseGame()
{
	system("cls");

	isPlayGame = false;

	int stateIndex = (int)state;
	int nextState = (int)state + 2;
	state = (State)nextState;

	mainLevel = levels[static_cast<int>(state)];
}

void GameManager::ResumeGame()
{
	system("cls");

	isPlayGame = true;

	int stateIndex = (int)state;
	int nextState = (int)state -2;
	state = (State)nextState;

	mainLevel = levels[static_cast<int>(state)];
}

GameManager& GameManager::Get()
{
	if (!instance)
	{
		std::cout << "Error : GameManager::Get(). instance is null.";
		__debugbreak();
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
	sprintf_s(scoreString, 128, "Score:%d", score);
	stringSize = strlen(scoreString);
	Renderer::Get().Submit(
		scoreString,
		Vector2((Engine::Get().GetWidth() / 2) - (static_cast<int>(stringSize) / 2), 
			Engine::Get().GetHeight() / 3 + 3)
	);
}

void GameManager::ShowStoreItem()
{
	sprintf_s(itemString, 32, "Boom : %d", Player::Get().ItemCount_Clear);
	stringSize = strlen(itemString);
	Renderer::Get().Submit(
		itemString,
		Vector2(Engine::Get().GetWidth() / 2 - (static_cast<int>(stringSize) / 2),
			Engine::Get().GetHeight() - 1)
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