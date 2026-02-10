#include "Bullet.h"
#include "Engine/Engine.h"
#include "Actor/BulletSpawner.h"

Bullet::Bullet(Vector2& position, float speed,float yPosition, float xPosition, int direction)
	:super("o", position, Color::Red),
			speed(speed), yPosition(static_cast<float>(position.y)),
			xPosition(static_cast<float>(position.x))
			
{
	this->direction = direction;
	sortingOrder = 1;
	SetPosition(position);
	SetDirection();
}

Bullet::~Bullet()
{
	BulletSpawner::Get().find(this);
}

void Bullet::Tick(float deltaTime)
{
	super::Tick(deltaTime);


	xPosition += static_cast<float>(DirX) * speed * deltaTime;
	yPosition += static_cast<float>(DirY) * speed * deltaTime;

	position.x = static_cast<int>(xPosition);
	position.y = static_cast<int>(yPosition);


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

void Bullet::SetDirection()
{
	// 방향 설정
	if (DirX == 0 && DirY == 0)
	{
		if (direction == 1) // 대각선 모드일 때
		{
			// 1. 가로 방향(DirX) 결정
			if (position.x <= 0) DirX = 1;
			else if (position.x >= Engine::Get().GetWidth() - 2) DirX = -1;

			// 중간쯤이면 가까운 쪽 반대로
			else DirX = (position.x < Engine::Get().GetWidth() / 2) ? 1 : -1; 

			// 2. 세로 방향(DirY) 결정
			if (position.y <= 0) DirY = 1;
			else if (position.y >= Engine::Get().GetHeight() - 1) DirY = -1;
			else DirY = (position.y < Engine::Get().GetHeight() / 2) ? 1 : -1;
		}
		// 위쪽
		else if (position.x > 0 && position.y == 0) { DirX = 0; DirY = 1;}
		// 아래쪽
		else if (position.x > 0 && position.y == Engine::Get().GetHeight() - 1) { DirX = 0; DirY = -1 ;}
		// 왼쪽
		else if (position.x == 0 && position.y > 0) { DirX = 1; DirY = 0; }
		// 오른쪽
		else if (position.x == Engine::Get().GetWidth() - 2 && position.y > 0) { DirX = -1; DirY = 0; }
	}
}


