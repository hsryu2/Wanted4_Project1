#pragma once

#include "Actor/Actor.h"
#include "Util/Timer.h"

using namespace Wanted;

class Player : public Actor
{

	RTTI_DECLARATIONS(Player, Actor)

public:
	Player();
	~Player();

	static Player& Get();

	void SetResistanceColor();
	void SetOriginalColor();

	int ItemCount_Clear = 5;

private:
	virtual void Tick(float deltaTime) override;

	// 오른쪽으로 이동하는 함수.
	void MoveRight(float deltaTime);
	
	// 왼쪽으로 이동하는 함수.
	void MoveLeft(float deltaTime);

	// 위로 이동하는 함수.
	void MoveUp(float deltaTime);

	// 아래로 이동하는 함수.
	void MoveDown(float deltaTime);


	// 아이템 사용
	void useItem_Clear(float deltaTime);


	
private:

	// 타이머 변수.
	Timer timer;

	float moveSpeed = 40.0f;
	float SlowMoveSpeed = 20.0f;

	float xf = 0.0f;

	float yf = 0.0f;

	static Player* instance;



};
