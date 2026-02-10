#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Level/Level.h"
#include "Render/Renderer.h"
#include "Level/GameLevel.h"
#include "Actor/BulletSpawner.h"

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
		// 게임 정지
		GameManager::Get().PauseGame();
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
	// 아이템 사용 키
	if (Input::Get().GetKeyDown('Q'))
	{
		useItem_Clear(deltaTime);
	}
	GameManager::Get().ShowStoreItem();
}


// 이동속도는 float으로 계산하고, 
// 좌표 검사 이후 형변환을 통해 실제 좌표 넣기.
// Space키를 누른채로 움직이면 느리게
void Player::MoveRight(float deltaTime)
{	
	// 오른쪽 이동 처리
	if (Input::Get().GetKey(VK_SPACE))
	{
		xf += SlowMoveSpeed * deltaTime;
	}
	else
	{
		xf += moveSpeed * deltaTime;
	}
	

	// 좌표 검사.
	if (xf + width > static_cast<float>(Engine::Get().GetWidth()))
	{
		xf = static_cast<float>(Engine::Get().GetWidth() - width);
	}

	position.x = static_cast<int>(xf);
}

void Player::MoveLeft(float deltaTime)
{
	// 왼쪽 이동 처리.
	if (Input::Get().GetKey(VK_SPACE))
	{
		xf -= SlowMoveSpeed * deltaTime;
	}
	else 
	{
		xf -= moveSpeed * deltaTime;
	}
	
	// 좌표 검사.
	if (xf < 0)
	{
		xf = 0;
	}
	position.x = static_cast<int>(xf);
}

void Player::MoveUp(float deltaTime)
{
	// 위쪽 이동 처리.
	if (Input::Get().GetKey(VK_SPACE))
	{
		yf -= SlowMoveSpeed * deltaTime;
	}
	else
	{
		yf -= moveSpeed * deltaTime;
	}
	
	if (yf < 0)
	{
		yf = 0;
	}
	position.y = static_cast<int>(yf);
}

void Player::MoveDown(float deltaTime)
{	
	// 아래쪽 이동 처리.
	if (Input::Get().GetKey(VK_SPACE))
	{
		yf += SlowMoveSpeed * deltaTime;
	}
	else
	{
		yf += moveSpeed * deltaTime;
	}
	
	// 좌표 검사.
	if (yf >= static_cast<float>(Engine::Get().GetHeight()))
	{
		yf -= 1.0f;
	}
	position.y = static_cast<int>(yf);

}

// Boom 아이템 사용
void Player::useItem_Clear(float deltaTime)
{
	if (ItemCount_Clear <= 0)
	{
		return;
	}
	ItemCount_Clear--;
	BulletSpawner::Get().ClearBullet();
}



Player& Player::Get()
{
	if (!instance)
	{
		std::cout << "Error: Player::Get(). instance is null\n";

		__debugbreak();
	}

	return *instance;
}

// 무적동안 플레이어 캐릭터 색상 변경
void Player::SetResistanceColor()
{	
	this->color = Color::Magenta;
	
}

void Player::SetOriginalColor()
{
	this->color = Color::Green;
}
