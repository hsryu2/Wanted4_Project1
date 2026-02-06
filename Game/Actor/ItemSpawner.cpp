#include "ItemSpawner.h"
#include "Util/Util.h"
#include "Engine/Engine.h"
#include "Level/GameLevel.h"
#include "Actor/Item.h"



ItemSpawner::ItemSpawner()
{
	timer.SetTargetTime(Util::RandomRange(1.0f, 2.0f));

}

ItemSpawner::~ItemSpawner()
{
}

void ItemSpawner::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	SpawnItem(deltaTime);
}

void ItemSpawner::SpawnItem(float deltaTime)
{
	timer.Tick(deltaTime);

	if (!timer.IsTimeOut())
	{
		return;
	}
	timer.Reset();

	ItemSpawnPosition();
	
	int itemtype = 0;
	itemtype = Util::Random(0, 0);

	Vector2 ItemPos(xPosition, yPosition);
	GetOwner()->AddNewActor(new Item(ItemPos, xPosition, yPosition, itemtype));

}

void ItemSpawner::ItemSpawnPosition()
{
	int xMax = Engine::Get().GetWidth();
	int yMax = Engine::Get().GetHeight();

	xPosition = Util::Random((xMax / 3), xMax - (xMax / 3));
	yPosition = Util::Random((yMax / 3), yMax - (yMax / 3));

}


