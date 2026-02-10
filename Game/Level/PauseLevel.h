#pragma once
#include "Level/Level.h"
#include "Math/Color.h"
#include "Level/GameLevel.h"
#include "Engine/Engine.h"


using namespace Wanted;

struct PauseMenuItem
{
	using OnSelected = void (*)();

	PauseMenuItem(const char* text, OnSelected onSelected)
		: onSelected(onSelected)
	{
		length = strlen(text);
		this->text = new char[length + 1];
		strcpy_s(this->text, length + 1, text);
	}

	~PauseMenuItem()
	{
		if (text)
		{
			delete[] text;
			text = nullptr;
		}
	}

	char* text = nullptr;
	size_t length = 0;
	OnSelected onSelected = nullptr;
};


class PauseLevel : public Level
{
	RTTI_DECLARATIONS(PauseLevel, Level)

public:
	PauseLevel();
	~PauseLevel();

private:
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

	int currentIndex = 0;
	std::vector<PauseMenuItem*> PMenuItems;

	Color SelectedColor = Color::Green;
	Color UnSelectedColor = Color::White;
};

