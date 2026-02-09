#include "ItemSpawner.h"
#include "Util/Util.h"
#include "Engine/Engine.h"
#include "Level/GameLevel.h"
#include "Actor/Item.h"



ItemSpawner::ItemSpawner()
{
	// 아이템 스폰 주기
	timer.SetTargetTime(Util::RandomRange(8.0f, 12.0f));

}

ItemSpawner::~ItemSpawner()
{
}

void ItemSpawner::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	SpawnItem(deltaTime);
}

// 아이템 스폰
void ItemSpawner::SpawnItem(float deltaTime) 
{
	timer.Tick(deltaTime);

	if (!timer.IsTimeOut())
	{
		return;
	}
	timer.Reset();

	ItemSpawnPosition();
	
	// 아이템 타입 정하기. 랜덤으로 지정.
	int itemtype = 0;
	itemtype = Util::Random(0, 1);

	Vector2 ItemPos(xPosition, yPosition);
	GetOwner()->AddNewActor(new Item(ItemPos, xPosition, yPosition, itemtype));

}

// 아이템 스폰 위치 정하기.
void ItemSpawner::ItemSpawnPosition() 
{
	int xMax = Engine::Get().GetWidth();
	int yMax = Engine::Get().GetHeight();

	xPosition = Util::Random((xMax / 3), xMax - (xMax / 3));
	yPosition = Util::Random((yMax / 3), yMax - (yMax / 3));

}


