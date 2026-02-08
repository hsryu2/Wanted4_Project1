#pragma once
#include "Level/Level.h"
#include "Math/Color.h"
#include "Engine/Engine.h"
#include "GameManager/GameManager.h"
#include "Core/Input.h"

using namespace Wanted;

struct EndMenuItem
{
	using OnSelected = void (*)();

	EndMenuItem(const char* text, OnSelected onSelected)
		: onSelected(onSelected)
	{
		size_t length = strlen(text) + 1;
		this->text = new char[length];
		strcpy_s(this->text, length, text);
	}

	~EndMenuItem()
	{
		if (text)
		{
			delete[] text;
			text = nullptr;
		}
	}

	char* text = nullptr;

	OnSelected onSelected = nullptr;
};

class EndLevel : public Level
{
	RTTI_DECLARATIONS(EndLevel, Level)

public:
	EndLevel();
	~EndLevel();

private:
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;


	int currentIndex = 0;
	std::vector<EndMenuItem*> EMenuItems;

	Color SelectedColor = Color::Green;
	Color UnSelectedColor = Color::White;

};

