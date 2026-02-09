#include "SpecialBullet.h"
#include "Engine/Engine.h"


SpecialBullet::SpecialBullet(Vector2& position, 
	float speed, float yPosition, 
	float xPosition, float fDirX, 
	float fDirY)

	: Bullet(position, speed, yPosition, xPosition, direction)
{
	sortingOrder = 2;

	Setimage("#");
	this->color = Color::YELLOW;
	this->speed = speed;
	this->xPosition = static_cast<float>(this->position.x);
	this->yPosition = static_cast<float>(this->position.y);
	this->fDirX = fDirX;
	this->fDirY = fDirY;

	SetPosition(position);
}

SpecialBullet::~SpecialBullet()
{
}

void SpecialBullet::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	SpecialShot(deltaTime);

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
}

void SpecialBullet::SpecialShot(float deltaTime)
{
	
	xPosition += fDirX * speed * deltaTime;
	yPosition += fDirY * speed * deltaTime;

	position.x = static_cast<int>(xPosition);
	position.y = static_cast<int>(yPosition);
}
