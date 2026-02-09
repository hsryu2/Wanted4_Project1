#pragma once
#include "Actor/Actor.h"
#include "Actor/Bullet.h"

using namespace Wanted;

class SpecialBullet : public Bullet
{
	RTTI_DECLARATIONS(SpecialBullet, Actor)

public:
	SpecialBullet(Vector2& position, float speed, float yPosition, float xPosition, float fDirX, float fDirY);
	~SpecialBullet();

private:
	virtual void Tick(float deltaTime) override;

	void SpecialShot(float deltaTime);

	float fDirX = 0.0f;
	float fDirY = 0.0f;
};

