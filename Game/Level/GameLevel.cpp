#include "GameLevel.h"
#include "Actor/Player.h"
#include "Actor/Bullet.h"
#include "Render/Renderer.h"
#include "Engine/Engine.h"
#include "Actor/BulletSpawner.h"
#include "Actor/HomingBullet.h"
#include "Actor/ItemSpawner.h"
#include "Actor/Item.h"
#include "Actor/SpecialBullet.h"

#include <iostream>

GameLevel::GameLevel()
{
	// Player 액터 추가.
	AddNewActor(new Player());

	AddNewActor(new BulletSpawner());
	
	AddNewActor(new ItemSpawner());

}

GameLevel::~GameLevel()
{
	BulletSpawner::Get().ClearPointerListOnly();
}

void GameLevel::PlayerResistance(float deltaTime)
{
	isPlayerResistance = true;
	timer.Reset();
	timer.SetTargetTime(3.0f);

	Player::Get().SetResistanceColor();
}

void GameLevel::TickResistance(float deltaTime)
{
	if (isPlayerResistance)
	{
		timer.Tick(deltaTime);
		if (timer.IsTimeOut())
		{
			isPlayerResistance = false;
			Player::Get().SetOriginalColor();
			timer.Reset();
		}

	}
}

void GameLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);


	// 1초당 점수 추가.
	GameManager::Get().Score(deltaTime);

	// 충돌 판정 처리.
	ProcessCollisionPlayerAndBullet();
	ProcessCollisionPlayerAndItem(deltaTime);

	// 무적 아이템 타이머
	TickResistance(deltaTime);
}

void GameLevel::Draw()
{
	super::Draw();

	if (isPlayerDead)
	{
		// 플레이어 죽음 메시지 Renderer에 제출.
		Renderer::Get().Submit("!Dead!", playerDeadPosition);

		// 점수 보여주기.
		GameManager::Get().ShowScore();

		// 화면에 바로 표시.
		Renderer::Get().PresentImmediately();

		// 프로그램 정지.
		Sleep(1000);

		// 게임 종료.
		GameManager::Get().EndGame();
		
	}

	// 점수 보여주기.
	GameManager::Get().ShowScore();
}


void GameLevel::ProcessCollisionPlayerAndBullet()
{
	// 액터 필터링을 위한 변수.
	Player* player = nullptr;
	std::vector<Actor*> bullets;

	// 액터 필터링.
	for (Actor* const actor : actors)
	{
		if (!player && actor->IsTypeOf<Player>())
		{
			player = actor->As<Player>();
			continue;
		}

		if (actor->IsTypeOf<Bullet>() || actor->IsTypeOf<HomingBullet>()|| actor->IsTypeOf<SpecialBullet>())
		{
			bullets.emplace_back(actor);
		}
	}

	// 판정 처리 안해도 되는지 확인.
	if (bullets.size() == 0 || !player)
	{
		return;
	}

	// 충돌 판정.
	for (Actor* const bullet : bullets)
	{
		if (bullet->TestIntersect(player) && isPlayerResistance == false)
		{

			if (Player::Get().ItemCount_Clear > 0)
			{
				BulletSpawner::Get().ClearBullet();
				Player::Get().ItemCount_Clear--;

				return;
			}
			// 플레이어 죽음 설정.
			isPlayerDead = true;

			// 죽은 위치 저장.
			playerDeadPosition = player->GetPosition();

			// 액터 제거 처리.
			player->Destroy();
			bullet->Destroy();
			break;
		}
	}
}

void GameLevel::ProcessCollisionPlayerAndItem(float deltaTime)
{
	// 액터 필터링을 위한 변수.
	Player* player = nullptr;
	std::vector<Actor*> items;

	// 액터 필터링.
	for (Actor* const actor : actors)
	{
		if (!player && actor->IsTypeOf<Player>())
		{
			player = actor->As<Player>();
			continue;
		}

		if (actor->IsTypeOf<Item>())
		{
			items.emplace_back(actor);
		}
	}

	// 판정 처리 안해도 되는지 확인.
	if (items.size() == 0 || !player)
	{
		return;
	}

	// 충돌 판정.
	for (Actor* const item : items)
	{
		if (item->TestIntersect(player))
		{
			// 액터 제거 처리 및 아이템 효과 적용.
			Item* collidedItem = item->As<Item>();

			if (collidedItem != nullptr)
			{
				int t = collidedItem->GetItemType();
				switch (t) {

				case 0: // 무적

					PlayerResistance(deltaTime);
					break;

				case 1: // 화면에 있는 모든 탄환 제거
					Player::Get().ItemCount_Clear++;
					break;

				case 2: // 화면에 있는 모든 총알 멈추기.
					
					break;

				}
				
			}
			item->Destroy();
		
			break;
		}
	}
}



