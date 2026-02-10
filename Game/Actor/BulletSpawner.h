#pragma once
#include "Actor/Actor.h"
#include "Util/Util.h"
#include "Util/Timer.h"
#include <vector>

using namespace Wanted;
class BulletSpawner : public Actor
{
	RTTI_DECLARATIONS(BulletSpawner, Actor)

public:
	BulletSpawner();
	~BulletSpawner();

	void ClearBullet();

	static BulletSpawner& Get();

	void find(Actor* bullet);

	void ClearPointerListOnly();

private:
	virtual void Tick(float deltaTime) override;

	void spawnBullet(float deltaTime);
	void spawnHomingBullet(float deltaTime);
	void spawnSpeBullet(float deltaTime);
	void spawnSpreadBullet(float deltaTime);

	void spawnPosition();
	void spawnSpeBulletPo();
	
	void ClearEffect(Vector2 position);

	std::vector<Actor*> activeBullets;

	int xPosition = 0;
	int yPosition = 0;

	float bulletSpeed = 0.0f;

	float currentAngle = 0.0f;

	bool isBulletSpawn = true;

	static BulletSpawner* instance;

	Timer timer;
	Timer HomingTimer;
	Timer SpecialTimer;
	Timer SpecialTimer2;
	Timer PatternA;
	Timer PatternB;
	Timer PatternC;
	
};

