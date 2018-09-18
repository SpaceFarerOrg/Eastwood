#include "UIManager.h"
#include "Graphics/RenderWindow.hpp"
#include "UISprite.h"

CUIManager::CUIManager()
{
}

CUIManager::~CUIManager()
{
}

void CUIManager::Init()
{
	myUI.AddElement(new CUISprite());

	myUI.Init();
}

void CUIManager::Update(float dt)
{
	myEvents.clear();

	myUI.Update();
}

void CUIManager::Render(sf::RenderWindow* aRenderWindow)
{
	myUI.Render(aRenderWindow);
}

bool CUIManager::CheckForEvent(const std::string & aEventName)
{
	bool rv = false;

	if (myEvents.find(aEventName) != myEvents.end())
	{
		rv = true;
	}

	return rv;
}
