#include "StartLevel.h"
#include "Render/Renderer.h"
#include "Core/Input.h"

StartLevel::StartLevel()
{
	MenuItems.emplace_back(new StartMenuItem(
		"Start Game",
		[]()
		{
			GameManager::Get().StartGame();
		}
	));
	MenuItems.emplace_back(new StartMenuItem(
		"End",
		[]()
		{
			Engine::Get().QuitEngine();
		}
	));
}

StartLevel::~StartLevel()
{
	for (StartMenuItem*& MenuItem : MenuItems)
	{
		delete MenuItem;
		MenuItem = nullptr;
	}
}

void StartLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	static int length = static_cast<int>(MenuItems.size());

	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		MenuItems[currentIndex]->onSelected();
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

void StartLevel::Draw()
{
	super::Draw();

	Renderer::Get().Submit("Console Dodge",
		Vector2(Engine::Get().GetWidth() / 2, Engine::Get().GetHeight() / 3),
		Color::White);

	for (int i = 0; i < static_cast<int>(MenuItems.size()); i++)
	{
		Color SelectedText = (i == currentIndex) ? SelectedColor : UnSelectedColor;

		Renderer::Get().Submit(
			MenuItems[i]->text,
			Vector2(Engine::Get().GetWidth() / 2, (Engine::Get().GetHeight() / 2) + i),
			SelectedText);
	}

}
