#pragma once
#include "Actor/Actor.h"
#include "Util/Timer.h"

using namespace Wanted;



class ItemSpawner : public Actor
{
	RTTI_DECLARATIONS(ItemSpawner, Actor)

public:
	ItemSpawner();
	~ItemSpawner();



private:
	virtual void Tick(float deltaTime) override;
	void SpawnItem(float deltaTime);
	void ItemSpawnPosition();

	int xPosition = 0;
	int yPosition = 0;
	Timer timer;

};

