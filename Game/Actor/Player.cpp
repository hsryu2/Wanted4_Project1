#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Level/Level.h"
#include "Render/Renderer.h"
#include "Level/GameLevel.h"

#include <iostream>

Player* Player::instance = nullptr;

Player::Player()
	: super("●", Vector2::Zero, Color::Green)
{
	instance = this;
	sortingOrder = 10;
	// 생성 위치 설정.
	int xPosition = (Engine::Get().GetWidth() / 2) - (width / 2);
	int yPosition = (Engine::Get().GetHeight() / 2);

	xf = static_cast<float>(xPosition);
	yf = static_cast<float>(yPosition);

	SetPosition(Vector2(xPosition, yPosition));
	
}

Player::~Player()
{
}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 종료 처리.
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		// 게임 종료.
		QuitGame();
	}

	// 경과 시간 업데이트.
	//elapsedTime += deltaTime;
	timer.Tick(deltaTime);

	// 좌우 방향키 입력처리.
	if (Input::Get().GetKey(VK_LEFT))
	{
		MoveLeft(deltaTime);
	}
	if (Input::Get().GetKey(VK_RIGHT))
	{
		MoveRight(deltaTime);
	}

	if (Input::Get().GetKey(VK_UP))
	{
		MoveUp(deltaTime);
	}
	if (Input::Get().GetKey(VK_DOWN))
	{
		MoveDown(deltaTime);
	}
}


// 이동속도는 float으로 계산하고, 
// 좌표 검사 이후 형변환을 통해 실제 좌표 넣기.
void Player::MoveRight(float deltaTime)
{
	xf += moveSpeed * deltaTime;

	// 좌표 검사.
	if (xf + width > static_cast<float>(Engine::Get().GetWidth()))
	{
		xf = static_cast<float>(Engine::Get().GetWidth() - width);
	}

	position.x = static_cast<int>(xf);
}

void Player::MoveLeft(float deltaTime)
{

	xf -= moveSpeed * deltaTime;

	// 왼쪽 이동 처리.
	//position.x -= 1;

	// 좌표 검사.
	if (xf < 0)
	{
		xf = 0;
	}
	position.x = static_cast<int>(xf);
}

void Player::MoveUp(float deltaTime)
{

	yf -= moveSpeed * deltaTime;
	// 위쪽 이동 처리.
	//position.y -= 1;

	if (yf < 0)
	{
		yf = 0;
	}
	position.y = static_cast<int>(yf);
}

void Player::MoveDown(float deltaTime)
{	

	// 아래쪽 이동 처리.
	//position.y += 1;
	yf += moveSpeed * deltaTime;

	if (yf >= static_cast<float>(Engine::Get().GetHeight()))
	{
		yf -= 1.0f;
	}
	position.y = static_cast<int>(yf);

}

Player& Player::Get()
{
	if (!instance)
	{
		std::cout << "Error: Player::Get(). instance is null\n";

		__debugbreak;
	}

	return *instance;
}

void Player::SetResistanceColor()
{	
	this->color = Color::YELLOW;
	
}

void Player::SetOriginalColor()
{
	this->color = Color::Green;
}
