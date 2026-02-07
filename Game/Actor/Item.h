#pragma once
#include "Actor/Actor.h"
#include "Util/Timer.h"

using namespace Wanted;

class Item : public Actor
{
	RTTI_DECLARATIONS(Item, Actor)

public:
	// int t -> 아이템 기능 분류용
	Item(Vector2& position, int xPosition, int yPosition, int itemType);
	~Item();
	
	int GetItemType();

	

private:
	virtual void Tick(float deltaTime) override;

	void SetColor();

	int xPosition = 0;
	int yPosition = 0;
	int ItemType = -1;
	Timer timer;
};

