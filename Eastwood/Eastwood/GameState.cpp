#include "GameState.h"
#include "InputManager.h"
#include <iostream>
#include "MenuState.h"

CGameState::CGameState()
{
}


CGameState::~CGameState()
{
}

void CGameState::Init()
{
	std::cout << "Pushed GameState" << std::endl;
}

void CGameState::Update(float dt)
{
	if (CInputManager::GetInstance().IsKeyPressed(EKeyCode::Escape))
	{
		PopAll();
	}
	if (CInputManager::GetInstance().IsKeyPressed(EKeyCode::BackSpace))
	{
		if (Pop())
		{
			std::cout << "Popped GameState" << std::endl;
		}
	}
	if (CInputManager::GetInstance().IsKeyPressed(EKeyCode::M))
	{
		Push(new CMenuState());
	}
}

void CGameState::Render(sf::RenderWindow * aRenderWindow)
{
}
