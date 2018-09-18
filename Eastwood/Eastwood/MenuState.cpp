#include "MenuState.h"
#include <iostream>
#include "InputManager.h"
#include "GameState.h"

CMenuState::CMenuState()
{
}

CMenuState::~CMenuState()
{
}

void CMenuState::Init()
{
	std::cout << "Pushed MenuState" << std::endl;

	myUIManager.Init();
}

void CMenuState::Update(float dt)
{
	if (CInputManager::GetInstance().IsKeyPressed(EKeyCode::Escape))
	{
		PopAll();
	}
	if (CInputManager::GetInstance().IsKeyPressed(EKeyCode::BackSpace))
	{
		if (Pop())
		{
			std::cout << "Popped MenuState" << std::endl;
		}
	}
	if (CInputManager::GetInstance().IsKeyPressed(EKeyCode::M))
	{
		Push(new CGameState());
	}

	myUIManager.Update(dt);
}

void CMenuState::Render(sf::RenderWindow * aRenderWindow)
{
	myUIManager.Render(aRenderWindow);
}
