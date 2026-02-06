#include "BulletSpawner.h"
#include "Level/Level.h"
#include "Actor/Bullet.h"
#include "Engine/Engine.h"
#include "Util/Util.h"
#include "Actor/HomingBullet.h"
#include "Actor/Player.h"


BulletSpawner::BulletSpawner()
{
	timer.SetTargetTime(Util::RandomRange(0.1f, 0.2f));
	HomingTimer.SetTargetTime(30.0f);
}

BulletSpawner::~BulletSpawner()
{
}

void BulletSpawner::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	spawnBullet(deltaTime);
	spawnHomingBullet(deltaTime);
}

void BulletSpawner::spawnBullet(float deltaTime)
{
	timer.Tick(deltaTime);

	if (!timer.IsTimeOut())
	{
		return;
	}

	timer.Reset();

	spawnPosition();

	bulletSpeed = Util::RandomRange(10.0f, 15.0f);

	Vector2 bulletPosition(xPosition, yPosition);

	GetOwner()->AddNewActor(
		new Bullet(bulletPosition, bulletSpeed, static_cast<float>(position.y), static_cast<float>(position.x)));
}

void BulletSpawner::spawnHomingBullet(float deltaTime)
{
	HomingTimer.Tick(deltaTime);

	if (!HomingTimer.IsTimeOut())
	{
		return;
	}
	HomingTimer.Reset();

	spawnPosition();

	bulletSpeed = 8.0f;

	Vector2 bulletPosition(xPosition, yPosition);

	GetOwner()->AddNewActor(
		new HomingBullet(bulletPosition,
			bulletSpeed,
			static_cast<float>(position.y),
			static_cast<float>(position.x)));
}

void BulletSpawner::spawnPosition()
{
	int side;
	side = Util::Random(0, 3);
	int xMax = Engine::Get().GetWidth();
	int yMax = Engine::Get().GetHeight();

	switch (side)
	{
	case 0: // 0 : 위쪽
		xPosition = Util::Random(1, xMax - 1);
		yPosition = 0;
		break;
	case 1: // 1 : 오른쪽
		xPosition = xMax - 2;
		yPosition = Util::Random(1, yMax);
		break;
	case 2: // 2 : 아래쪽
		xPosition = Util::Random(1, xMax - 1);
		yPosition = yMax - 1;
		break;
	case 3: // 3 : 왼쪽
		xPosition = 0;
		yPosition = Util::Random(1, yMax);
		break;

	}
}
