#pragma once
#include "Actor/Actor.h"

using namespace Wanted;

class Bullet : public Actor
{
	RTTI_DECLARATIONS(Bullet, Actor)

	enum class MoveDirection
	{
		None = -1,
		Straight,
		Homing
	};

public:
	Bullet(Vector2& position, float speed, float yPosition, float xPosition);
	~Bullet();
	
private:
	virtual void Tick(float deltaTime) override;

protected:


	//void FireLeft(float deltaTime);
	//void FireRight(float deltaTime);
	//void FireUp(float deltaTime);
	//void FireDown(float deltaTime);

	//MoveDirection direction = MoveDirection::None;

	float speed = 3.0f;

	float yPosition = 0.0f;
	float xPosition = 0.0f;

	// 총알이 나가는 방향 정하기 위한 변수.
	int DirX = 0;
	int DirY = 0;

};

