#include "HomingBullet.h"
#include "Actor/Player.h"

HomingBullet::HomingBullet(Vector2& position, float speed, float yPosition, float xPosition)
	: Bullet(position, speed, yPosition, xPosition, direction)

{	// 유도탄 이미지, 색 설정.

	sortingOrder = 2;

	Setimage("@");
	this->color = Color::Blue;
	this->speed = speed;
	this->xPosition = static_cast<float>(this->position.x);
	this->yPosition = static_cast<float>(this->position.y);

	SetPosition(position);
}

HomingBullet::~HomingBullet()
{
}

	
void HomingBullet::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	Shot(deltaTime);

	SetPosition(position);
}

void HomingBullet::Shot(float deltaTime) {

	Vector2 targetpos = Player::Get().GetPosition();

	// 1. X축 유도
	if (targetpos.x > position.x)      xPosition += speed * deltaTime; // 오른쪽으로 이동
	else if (targetpos.x < position.x) xPosition -= speed * deltaTime; // 왼쪽으로 이동

	// 2. Y축 유도
	if (targetpos.y > position.y)      yPosition += speed * deltaTime; // 아래쪽으로 이동
	else if (targetpos.y < position.y) yPosition -= speed * deltaTime; // 위쪽으로 이동


	position.x = static_cast<int>(xPosition);
	position.y = static_cast<int>(yPosition);


	
}



