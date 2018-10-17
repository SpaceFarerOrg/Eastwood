#include "ControlComponent.h"
#include "InputManager.h"
#include "CommonMath.h"

sf::Vector2f CControlComponent::GetDirection()
{
	CInputManager& im = CInputManager::GetInstance();
	sf::Vector2f dir;

	if (im.IsKeyDown(EKeyCode::Left) || im.IsKeyDown(EKeyCode::A))
	{
		dir.x += -1;
	}
	if (im.IsKeyDown(EKeyCode::Up) || im.IsKeyDown(EKeyCode::W))
	{
		dir.y -= 1;
	}
	if (im.IsKeyDown(EKeyCode::Right) || im.IsKeyDown(EKeyCode::D))
	{
		dir.x += 1;
	}
	if (im.IsKeyDown(EKeyCode::Down) || im.IsKeyDown(EKeyCode::S))
	{
		dir.y += 1;
	}

	return Math::GetNormalized(dir);
}
