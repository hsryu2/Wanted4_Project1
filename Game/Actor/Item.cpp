#include "Item.h"
#include "Level/GameLevel.h"

Item::Item(Vector2& position, int xPosition, int yPosition,int itemType)
	: super("I", position, Color::YELLOW), xPosition(position.x), yPosition(position.y)
{	
	this->ItemType = itemType;
	SetPosition(position);
}

Item::~Item()
{
}


int Item::GetItemType()
{
	return this->ItemType;
}

void Item::Tick(float deltaTime)
{
	super::Tick(deltaTime);
}
