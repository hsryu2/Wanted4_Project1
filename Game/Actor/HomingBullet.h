#pragma once
#include "Actor/Actor.h"
#include "Actor/Bullet.h"

using namespace Wanted;

class HomingBullet : public Actor
{
	RTTI_DECLARATIONS(HomingBullet, Actor)

public:
	HomingBullet(Vector2& position, float speed, float yPosition, float xPosition);
	~HomingBullet();

private:
	virtual void Tick(float deltaTime) override;
	
	Actor* target = nullptr;
	float speed = 3.0f;
	float yPosition = 0.0f;
	float xPosition = 0.0f;

};

