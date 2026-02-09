#include "BulletSpawner.h"
#include "Level/Level.h"
#include "Actor/Bullet.h"
#include "Engine/Engine.h"
#include "Util/Util.h"
#include "Actor/HomingBullet.h"
#include "Actor/Player.h"
#include "Actor/SpecialBullet.h"


#include <math.h>
#include <iostream>

BulletSpawner* BulletSpawner::instance = nullptr;

BulletSpawner::BulletSpawner()
{
	instance = this;

	// 시간 설정.
	timer.SetTargetTime(Util::RandomRange(0.1f, 0.3f));
	HomingTimer.SetTargetTime(3.0f);
	SpecialTimer.SetTargetTime(0.05f);
	a.SetTargetTime(2.0f);

	isBulletSpawn = true;
}

BulletSpawner::~BulletSpawner()
{
}

BulletSpawner& BulletSpawner::Get() {
	
	if (!instance) {
		
		std::cout << "Error : BulletSpawner::Get(). instance is null";
		__debugbreak();
	}

	return *instance;
}

void BulletSpawner::find(Actor* bullet)
{
	if (activeBullets.empty())
	{
		return;
	}
	// 리스트를 돌면서 넘겨받은 주소(bullet)와 일치하는 탄환 찾기.
	for (auto it = activeBullets.begin(); it != activeBullets.end(); ++it)
	{
		if (*it == bullet)
		{
			activeBullets.erase(it); // 찾으면 리스트에서 삭제
			return; // 찾았으니 함수 종료
		}
	}
}

void BulletSpawner::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	a.Tick(deltaTime);

	if (a.IsTimeOut()) // 현재 진행 중인 패턴 시간이 다 되면
	{
		if (isBulletSpawn) // 일반 패턴 도중
		{
			ClearBullet();        // 기존 탄막 제거
			isBulletSpawn = false; // 특수 패턴으로 변경
			a.SetTargetTime(5.0f);
		}
		else // 특수 패턴 중
		{
			isBulletSpawn = true;  // 다시 일반 패턴으로 변경
			// 일반 패턴을 유지할 시간만큼 타이머 재설정
			a.SetTargetTime(12.0f);
		}

		a.Reset();
	}
	
	if(isBulletSpawn)
	{
		spawnBullet(deltaTime);
		spawnHomingBullet(deltaTime);
	}
	else
	{	
		spawnSpeBullet(deltaTime);
	}
}

// 일반 탄환 생성.
void BulletSpawner::spawnBullet(float deltaTime) 
{
	timer.Tick(deltaTime);

	if (!timer.IsTimeOut())
	{
		return;
	}

	timer.Reset();

	spawnPosition();

	// 불렛 스피드 및 대각선 or 직선 탄환 정하기. 랜덤으로 지정.
	bulletSpeed = Util::RandomRange(10.0f, 15.0f);
	int SetDirection = Util::Random(0, 1);
	Vector2 bulletPosition(xPosition, yPosition);

	Bullet* newBullet = new Bullet(
		bulletPosition,
		bulletSpeed,
		static_cast<float>(position.y),
		static_cast<float>(position.x),
		SetDirection);
	GetOwner()->AddNewActor(newBullet);

	// 전체 탄막 사라지게 하기 위해서 따로 탄환을 담아둘 객체에도 넣어줌.
	activeBullets.emplace_back(newBullet);
}

void BulletSpawner::spawnHomingBullet(float deltaTime) // 유도탄 생성
{
	HomingTimer.Tick(deltaTime);

	if (!HomingTimer.IsTimeOut())
	{
		return;
	}
	HomingTimer.Reset();

	spawnPosition();

	bulletSpeed = Util::RandomRange(10.0f, 15.0f);

	Vector2 bulletPosition(xPosition, yPosition);


	HomingBullet* newBullet = new HomingBullet(
		bulletPosition,
		bulletSpeed,
		static_cast<float>(position.y),
		static_cast<float>(position.x));
	GetOwner()->AddNewActor(newBullet);
	activeBullets.emplace_back(newBullet);

}

// 특수패턴 탄환 생성.
void BulletSpawner::spawnSpeBullet(float deltaTime)
{
	SpecialTimer.Tick(deltaTime);

	if (!SpecialTimer.IsTimeOut())
	{
		return;
	}

	if (SpecialTimer.IsTimeOut())
	{
		bulletSpeed = Util::RandomRange(10.0f, 20.0f);
		spawnSpeBulletPo();
		Vector2 bulletPosition1(xPosition / 2, yPosition);
		Vector2 bulletPosition2(xPosition * 1.5f, yPosition);
		float radian = currentAngle * (3.141592f / 180.0f);

		// 2. 각도에 따른 방향 벡터 계산
		float fDirX = cosf(radian);
		float fDirY = sinf(radian);


		// 탄환 생성
		SpecialBullet* newBullet1 = new SpecialBullet(
			bulletPosition1,
			bulletSpeed,
			static_cast<float>(position.y),
			static_cast<float>(position.x),
			fDirX, fDirY);
		GetOwner()->AddNewActor(newBullet1);
		activeBullets.emplace_back(newBullet1);

		SpecialBullet* newBullet2 = new SpecialBullet(
			bulletPosition2,
			bulletSpeed,
			static_cast<float>(position.y),
			static_cast<float>(position.x),
			fDirX, fDirY);
		GetOwner()->AddNewActor(newBullet2);
		activeBullets.emplace_back(newBullet2);

		currentAngle += bulletSpeed;
		if (currentAngle >= 360.0f) currentAngle -= 360.0f;

		
	}
	SpecialTimer.Reset();

}

// 불렛 스폰 위치 정하기.
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

void BulletSpawner::spawnSpeBulletPo()
{
	xPosition = Engine::Get().GetWidth() / 2;
	yPosition = Engine::Get().GetHeight() / 2;

}

// 전체 탄막 지우기 아이템 획득시 호출되는 함수.
void BulletSpawner::ClearBullet()
{
	for (Actor* bullet : activeBullets)
	{
		bullet->Destroy();
	}

	activeBullets.clear();
}

// 레벨을 바꿀 때 사용할 객체 비우기.
void BulletSpawner::ClearPointerListOnly() {
	activeBullets.clear();
}