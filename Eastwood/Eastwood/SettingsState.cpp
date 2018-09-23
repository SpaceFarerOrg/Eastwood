#include "SettingsState.h"

void CSettingsState::Init()
{
	myUIManager.Init("UI/settings_menu.json");
}

void CSettingsState::Update(float dt)
{
	myUIManager.Update(dt);
}

void CSettingsState::Render(sf::RenderWindow * aRenderWindow)
{
	myUIManager.Render(aRenderWindow);
}
