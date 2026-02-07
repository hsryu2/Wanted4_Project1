#pragma once
#include "Actor/Actor.h"

using namespace Wanted;

class Bullet : public Actor
{
	RTTI_DECLARATIONS(Bullet, Actor)

public:
	Bullet(Vector2& position, float speed, float yPosition, float xPosition, int direction);
	~Bullet();
	
private:
	virtual void Tick(float deltaTime) override;
	void SetDirection();

protected:

	int direction = 0;
	
	// 대각선 쏘는 방향 정하기.
	// d = 0 우하단
	// d = 1 우상단
	// d = 2 좌상단
	// d = 3 좌하단

	int d = -1;

	float speed = 0.0f;

	float yPosition = 0.0f;
	float xPosition = 0.0f;

	// 총알이 나가는 방향 정하기 위한 변수.
	int DirX = 0;
	int DirY = 0;


};

