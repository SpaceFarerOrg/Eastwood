#include "HostState.h"

#include <iostream>

#include "InputManager.h"
#include "UITextInput.h"

void CHostState::Init()
{
	myUIManager.Init("UI/host_menu.json");
}

void CHostState::Update(float dt)
{
	myUIManager.Update(dt);
	if (CInputManager::GetInstance().IsKeyPressed(EKeyCode::Enter))
	{
		CUITextInput* textInput = myUIManager.GetElement<CUITextInput>("textinput");
		std::cout << textInput->GetText() << std::endl;
	}
}

void CHostState::Render(sf::RenderWindow * aRenderWindow)
{
	myUIManager.Render(aRenderWindow);
}
