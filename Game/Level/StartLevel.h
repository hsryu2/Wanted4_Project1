#pragma once
#include "Level/Level.h"
#include "GameManager/GameManager.h"
#include "Math/Color.h"
#include "Render/Renderer.h"
using namespace Wanted;

struct StartMenuItem
{
	using OnSelected = void (*)();

	StartMenuItem(const char* text, OnSelected onSelected)
		: onSelected(onSelected)
	{
		length = strlen(text);
		this->text = new char[length + 1];
		strcpy_s(this->text, length + 1, text);
	}

	~StartMenuItem()
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



class StartLevel : public Level
{
	RTTI_DECLARATIONS(StartLevel, Level)

public:
	StartLevel();
	~StartLevel();


private:
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;


	std::vector<StartMenuItem*> MenuItems;

	Color SelectedColor = Color::Green;
	Color UnSelectedColor = Color::White;
	int currentIndex = 0;
};

