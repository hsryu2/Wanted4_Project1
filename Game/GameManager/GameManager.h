#pragma once
#include "Engine/Engine.h"
#include "Level/GameLevel.h"
#include "Level/StartLevel.h"
#include "Level/EndLevel.h"
#include "Level/Level.h"

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

	void Score(float deltaTime);
	void ShowScore();
	void ShowEndScore();
	void ShowStoreItem();


	static GameManager& Get();

private:


	std::vector<Level*> levels;

	State state = State::GamePlay;

	// 게임하는 상태인지 확인
	bool isPlayGame = false;

	// 점수 변수.
	int score = 0;
	float scoreAccumulator = 0.0f;

	// 점수 문자열.
	char scoreString[128] = {};

	// 아이템 문자열.
	char itemString[32] = {};

	static GameManager* instance;
};

