#include "UseItemEffect.h"

UseItemEffect::UseItemEffect(Vector2 position, float DirX, float DirY, float spd, Color color)
	: Actor("*", position, color),  speed(spd)
{
	this->DirX = DirX;
	this->DirY = DirY;
	this->position = position;
	xPosition = position.x;
	yPosition = position.y;

	sortingOrder = 0; 

	SetPosition(position);
}


UseItemEffect::~UseItemEffect()
{
}

void UseItemEffect::EffectShot(float deltaTime)
{
	xPosition += DirX * speed * deltaTime;
	yPosition += DirY * speed * deltaTime;

	position.x = static_cast<int>(xPosition);
	position.y = static_cast<int>(yPosition);
}

void UseItemEffect::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	timer += deltaTime;

	if (timer >= lifeTime) {
		Destroy(); // 시간이 다 되면 삭제
		return;
	}
	EffectShot(deltaTime);

}
