#include "HomingBullet.h"
#include "Actor/Player.h"

HomingBullet::HomingBullet(Vector2& position, float speed, float yPosition, float xPosition)
	: super("@", position, Color::Blue),
	speed(speed),
	yPosition(static_cast<float>(position.y)),
	xPosition(static_cast<float>(position.x))
{
}

HomingBullet::~HomingBullet()
{
}

	
void HomingBullet::Tick(float deltaTime)
{
	super::Tick(deltaTime);

}

