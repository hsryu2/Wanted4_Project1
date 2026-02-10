#include "BulletSpawner.h"
#include "Level/Level.h"
#include "Actor/Bullet.h"
#include "Engine/Engine.h"
#include "Util/Util.h"
#include "Actor/HomingBullet.h"
#include "Actor/Player.h"
#include "Actor/SpecialBullet.h"
#include "Actor/UseItemEffect.h"


#include <math.h>
#include <iostream>

BulletSpawner* BulletSpawner::instance = nullptr;

BulletSpawner::BulletSpawner()
{
	instance = this;

	// 탄환 생성 주기 설정.

	// 일반탄
	timer.SetTargetTime(Util::RandomRange(0.1f, 0.2f));
	
	// 유도탄
	HomingTimer.SetTargetTime(Util::RandomRange(2.5f, 4.0f));

	// 특수패턴 탄
	SpecialTimer.SetTargetTime(0.03f);

	// 일반 패턴 강화 탄막
	SpecialTimer2.SetTargetTime(0.2f);

	// 게임 시작 이후 첫 패턴 시간 설정

	// 첫 특수 탄막 패턴 시작 시간
	PatternA.SetTargetTime(5.0f);

	// 일반 패턴 강화 탄막 시작 시간
	PatternB.SetTargetTime(10.0f);

	// 전체 패턴 강화 시작 시간
	PatternC.SetTargetTime(20.0f);

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

// 전체 탄막 지우기 위한 활동중인 bullet 객체 찾는 함수.
void BulletSpawner::find(Actor* bullet)
{
	// 활동중인 탄환이 없으면 리턴.
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
			return;
		}
	}
}

void BulletSpawner::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	PatternA.Tick(deltaTime);
	PatternB.Tick(deltaTime);
	PatternC.Tick(deltaTime);

	if (PatternA.IsTimeOut()) // 현재 진행 중인 패턴 시간이 다 되면
	{
		if (isBulletSpawn) // 일반 패턴 도중
		{
			ClearBullet();        // 기존 탄막 제거
			isBulletSpawn = false; // 특수 패턴으로 변경
			PatternA.SetTargetTime(5.0f);
		}
		else // 특수 패턴 중
		{
			isBulletSpawn = true;  // 다시 일반 패턴으로 변경
			// 일반 패턴을 유지할 시간만큼 타이머 재설정
			PatternA.SetTargetTime(12.0f);
		}

		PatternA.Reset();
	}
	
	// 특수 패턴 여부
	// 특수패턴 중에는 일반 탄환 생성 X
	if(isBulletSpawn)
	{
		spawnBullet(deltaTime);
		spawnHomingBullet(deltaTime);
		if (PatternB.IsTimeOut())
		{
			spawnSpreadBullet(deltaTime);
		}

	}
	
	// 특수패턴 시작
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
	// 시간이 지나면 더욱 빨라지도록 스피드 설정
	if (PatternC.IsTimeOut())
	{
		bulletSpeed = Util::RandomRange(15.0f, 22.5f);
	}
	else
	{
		bulletSpeed = Util::RandomRange(10.0f, 15.0f);
	}

	// 매 프레임마다 탄환 생성 주기가 줄어들도록 만들었음.
	float currentRate = timer.GetTargetTime();
	if (currentRate > 0.05f)
	{
		
		timer.SetTargetTime(currentRate - 0.001f * deltaTime);
	}
	
	// 대각선 탄환 결정
	int SetDirection = Util::Random(0, 1);
	Vector2 bulletPosition(xPosition, yPosition);

	Bullet* newBullet = new Bullet(
		bulletPosition,
		bulletSpeed,
		static_cast<float>(position.y),
		static_cast<float>(position.x),
		SetDirection);
	GetOwner()->AddNewActor(newBullet);

	// 전체 탄막 지우기 아이템을 위해서 따로 탄환을 담아둘 객체에도 넣어줌.
	activeBullets.emplace_back(newBullet);
}


// 유도탄 생성
void BulletSpawner::spawnHomingBullet(float deltaTime) 
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
// 시간이 지나면 더욱 빨라지도록 스피드 설정
void BulletSpawner::spawnSpeBullet(float deltaTime)
{
	SpecialTimer.Tick(deltaTime);

	if (!SpecialTimer.IsTimeOut())
	{
		return;
	}

	if (SpecialTimer.IsTimeOut())
	{
		if (PatternC.IsTimeOut())
		{
			bulletSpeed = Util::RandomRange(15.0f, 30.0f);
		}
		else
		{
			bulletSpeed = Util::RandomRange(10.0f, 20.0f);
		}

		// 위치 설정
		spawnSpeBulletPo();
		Vector2 bulletPosition1(xPosition / 2, yPosition);
		Vector2 bulletPosition2(xPosition * 1.5f, yPosition);
		float radian = currentAngle * (3.141592f / 180.0f);

		// 각도에 따른 방향 벡터 계산
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

// 10초 이후부터는 일반 패턴 강화.
void BulletSpawner::spawnSpreadBullet(float deltaTime)
{
	SpecialTimer2.Tick(deltaTime);

	if (!SpecialTimer2.IsTimeOut())
	{
		return;
	}

	if (SpecialTimer2.IsTimeOut())
	{
		
		if (PatternC.IsTimeOut())
		{
			bulletSpeed = 18.0f;
		}
		else
		{
			bulletSpeed = 12.0f;
		}

		spawnSpeBulletPo();
		Vector2 bulletPosition(xPosition, yPosition);
		float radian = currentAngle * (3.141592f / 180.0f);

		// 2. 각도에 따른 방향 벡터 계산
		float fDirX = cosf(radian);
		float fDirY = sinf(radian);


		// 탄환 생성
		SpecialBullet* newBullet = new SpecialBullet(
			bulletPosition,
			bulletSpeed,
			static_cast<float>(position.y),
			static_cast<float>(position.x),
			fDirX, fDirY);
		GetOwner()->AddNewActor(newBullet);
		activeBullets.emplace_back(newBullet);

		currentAngle += bulletSpeed;
		if (currentAngle >= 360.0f) currentAngle -= 360.0f;


	}
	SpecialTimer2.Reset();
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

// 탄막 클리어 효과.
void BulletSpawner::ClearEffect(Vector2 position)
{
	// 8방향으로 퍼지는 효과
	float angles[] = { 0, 30, 45, 60, 90, 120 , 135, 150, 180, 210, 225, 240, 270, 300, 315, 330 };

	for (float angle : angles)
	{
		float radian = angle * (3.141592f / 180.0f);

		float fDirX = cosf(radian);
		float fDirY = sinf(radian);
		

		// 아이템 종류에 따라 다른 색상의 입자 생성
		UseItemEffect* p = new UseItemEffect(position, fDirX, fDirY, 20.0f, Color::Cyan);
		GetOwner()->AddNewActor(p);
		
	}
}

// 전체 탄막 지우기 아이템 획득시 호출되는 함수.
void BulletSpawner::ClearBullet()
{
	for (Actor* bullet : activeBullets)
	{
		bullet->Destroy();
	}
	ClearEffect(Player::Get().GetPosition());
	activeBullets.clear();
}

// 레벨을 바꿀 때 사용할 객체 비우기.
void BulletSpawner::ClearPointerListOnly() {
	activeBullets.clear();
}