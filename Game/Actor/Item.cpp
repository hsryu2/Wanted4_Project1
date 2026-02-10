#include "Item.h"
#include "Level/GameLevel.h"

Item::Item(Vector2& position, int xPosition, int yPosition,int itemType)
	: super("¡Ú", position), xPosition(position.x), yPosition(position.y)
{	
	this->ItemType = itemType;
	
	sortingOrder = 5;

	SetColor();
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

void Item::SetColor()
{
	if (this->ItemType == 0)
	{
		this->color = Color::Magenta;
	}
	else if (this->ItemType == 1)
	{
		this->color = Color::White;
	}
}
