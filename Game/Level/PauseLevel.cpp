#include "PauseLevel.h"
#include "Core/Input.h"


PauseLevel::PauseLevel()
{
	PMenuItems.emplace_back(new PauseMenuItem(
		"Resume Game",
		[]()
		{
			GameManager::Get().ResumeGame();
		}
	));
	PMenuItems.emplace_back(new PauseMenuItem(
		"Restart",
		[]()
		{
			GameManager::Get().Restart();
		}
	));
	PMenuItems.emplace_back(new PauseMenuItem(
		"Quit",
		[]()
		{
			Engine::Get().QuitEngine();
		}
	));
}

PauseLevel::~PauseLevel()
{
}

void PauseLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	static int length = static_cast<int>(PMenuItems.size());

	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		PMenuItems[currentIndex]->onSelected();
		currentIndex = 0;
	}
	if (Input::Get().GetKeyDown(VK_UP))
	{
		currentIndex = (currentIndex - 1 + length) % length;
	}
	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		currentIndex = (currentIndex + 1) % length;
	}

	// 일시정지 화면에서 Resume Game을 선택하지 않아도 ESC키로 처리 가능.
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		GameManager::Get().ResumeGame();
	}
}


void PauseLevel::Draw()
{
	for (int i = 0; i < static_cast<int>(PMenuItems.size()); i++)
	{
		Color SelectedText = (i == currentIndex) ? SelectedColor : UnSelectedColor;

		Renderer::Get().Submit(
			PMenuItems[i]->text,
			Vector2(Engine::Get().GetWidth() / 2 - (PMenuItems[i]->length) / 2, (Engine::Get().GetHeight() / 2) + i * 2),
			SelectedText);
	}
}
