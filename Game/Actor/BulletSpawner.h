#pragma once
#include "Actor/Actor.h"
#include "Util/Util.h"
#include "Util/Timer.h"

using namespace Wanted;
class BulletSpawner : public Actor
{
	RTTI_DECLARATIONS(BulletSpawner, Actor)

public:
	BulletSpawner();
	~BulletSpawner();

private:
	virtual void Tick(float deltaTime) override;

	void spawnBullet(float deltaTime);
	void spawnHomingBullet(float deltaTime);

	void spawnPosition();

	int xPosition = 0;
	int yPosition = 0;

	float bulletSpeed = 0.0f;


	Timer timer;
	Timer HomingTimer;
};

