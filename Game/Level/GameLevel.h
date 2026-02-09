#pragma once

#include "Level/Level.h"
#include "Math/Vector2.h"
#include "Util/Timer.h"
#include "GameManager/GameManager.h"

using namespace Wanted;

class GameLevel : public Level
{
	// RTTI 등록.
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();
	~GameLevel();
	
private:

	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

	void PlayerResistance(float deltaTime);
	void TickResistance(float deltaTime);

	// 충돌 판정 처리 함수.
	void ProcessCollisionPlayerAndBullet();
	void ProcessCollisionPlayerAndItem(float deltaTime);


private:

	// 플레이어가 죽었는지 확인.
	bool isPlayerDead = false;

	// 플레이어가 무적 상태인지 확인.
	bool isPlayerResistance = false;

	// 플레이어가 죽은 위치 (Draw에서 처리하기 위해 Tick에서 저장).
	Vector2 playerDeadPosition;


	Timer timer;
};
