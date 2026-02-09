#include "EndLevel.h"


EndLevel::EndLevel()
{
	EMenuItems.emplace_back(new EndMenuItem(
		"Restart",
		[]()
		{
			GameManager::Get().Restart();
		}
	));
	EMenuItems.emplace_back(new EndMenuItem(
		"End",
		[]()
		{
			Engine::Get().QuitEngine();
		}
	));
}

EndLevel::~EndLevel()
{
	for (EndMenuItem*& EMenuItem : EMenuItems)
	{
		delete EMenuItem;
		EMenuItem = nullptr;
	}
}

void EndLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	static int length = static_cast<int>(EMenuItems.size());

	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		EMenuItems[currentIndex]->onSelected();
	}
	if (Input::Get().GetKeyDown(VK_UP))
	{
		currentIndex = (currentIndex - 1 + length) % length;
	}
	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		currentIndex = (currentIndex + 1) % length;
	}
}

void EndLevel::Draw()
{
	super::Draw();

	Renderer::Get().Submit("Game Over",
		Vector2(Engine::Get().GetWidth() / 2, Engine::Get().GetHeight() / 3),
		Color::White);

	GameManager::Get().ShowEndScore();
	

	for (int i = 0; i < static_cast<int>(EMenuItems.size()); i++)
	{
		Color SelectedText = (i == currentIndex) ? SelectedColor : UnSelectedColor;

		Renderer::Get().Submit(
			EMenuItems[i]->text,
			Vector2(Engine::Get().GetWidth() / 2, (Engine::Get().GetHeight() / 2) + i),
			SelectedText);
	}
}
