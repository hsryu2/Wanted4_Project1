#pragma once
#include "Actor/Actor.h"
#include "Actor/Bullet.h"
#include "Actor/Player.h"

using namespace Wanted;

class HomingBullet : public Bullet
{
	RTTI_DECLARATIONS(HomingBullet, Actor)

public:
	HomingBullet(Vector2& position, float speed, float yPosition, float xPosition);
	~HomingBullet();


	void Shot(float deltaTime);
private:
	virtual void Tick(float deltaTime) override;
	
	float speed = 0.0f;
	float yPosition = 0.0f;
	float xPosition = 0.0f;

};

