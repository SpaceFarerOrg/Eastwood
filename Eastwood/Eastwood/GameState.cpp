#include "GameState.h"
#include "InputManager.h"

CGameState::CGameState()
{
}


CGameState::~CGameState()
{
}

void CGameState::Init()
{
}

void CGameState::Update(float dt)
{
	if (CInputManager::GetInstance().IsKeyPressed(EKeyCode::Escape))
	{
		PopAll();
	}
}

void CGameState::Render(sf::RenderWindow * aRenderWindow)
{
}
