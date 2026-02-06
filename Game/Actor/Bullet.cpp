#include "Bullet.h"
#include "Engine/Engine.h"
#include "Actor/BulletSpawner.h"

Bullet::Bullet(Vector2& position, float speed,float yPosition, float xPosition)
	:super("*", position, Color::Red),
			speed(speed), yPosition(static_cast<float>(position.y)),
			xPosition(static_cast<float>(position.x))
			

{
	sortingOrder = 1;
	SetPosition(position);
}

Bullet::~Bullet()
{
	BulletSpawner::Get().find(this);
}

void Bullet::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	if (DirX == 0 && DirY == 0)
	{
		// 위쪽
		if (position.x > 0 && position.y == 0) { DirX = 0; DirY = 1; }
		// 아래쪽
		else if (position.x > 0 && position.y == Engine::Get().GetHeight() - 1) { DirX = 0; DirY = -1; }
		// 왼쪽
		else if (position.x == 0 && position.y > 0) { DirX = 1; DirY = 0; }
		// 오른쪽
		else if (position.x == Engine::Get().GetWidth() - 2 && position.y > 0) { DirX = -1; DirY = 0; }
	}

	// 위에서 아래로 쏘기.
	if (DirX == 0 && DirY == 1)
	{
		yPosition = yPosition + speed * deltaTime;
		position.y = static_cast<int>(yPosition);
	}
	// 아래에서 위로 쏘기.
	else if (DirX == 0 && DirY == -1)
	{
		yPosition = yPosition - speed * deltaTime;
		position.y = static_cast<int>(yPosition);
	}
	// 왼쪽에서 오른쪽으로 쏘기.
	else if (DirX == 1 && DirY == 0)
	{
		xPosition = xPosition + speed * deltaTime * 1.4f;
		position.x = static_cast<int>(xPosition);
	}
	// 오른쪽에서 왼쪽으로 쏘기.
	else if (DirX == -1 && DirY == 0)
	{
		xPosition = xPosition - speed * deltaTime * 1.4f;
		position.x = static_cast<int>(xPosition);
	}

	// 탄환이 콘솔 사이즈 끝에 도달 시 파괴
	if (position.x > Engine::Get().GetWidth())
	{
		Destroy();
		return;
	}
	if (position.x < 0)
	{
		Destroy();
		return;
	}
	if (position.y > Engine::Get().GetHeight())
	{
		Destroy();
		return;
	}
	if (position.y < 0)
	{
		Destroy();
		return;
	}

	SetPosition(position);
}

//void Bullet::FireLeft(float deltaTime)
//{
//
//}
//
//void Bullet::FireRight(float deltaTime)
//{
//}
//
//void Bullet::FireUp(float deltaTime)
//{
//
//}
//
////탄환이 위쪽에서 스폰 됐을 때 쏘는 방향 = 아래 직선
//void Bullet::FireDown(float deltaTime)
//{
//
//}

