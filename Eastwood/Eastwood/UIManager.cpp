#include "UIManager.h"
#include "Graphics/RenderWindow.hpp"
#include "UISprite.h"

#include "JsonDocument.h"

CUIManager::CUIManager()
{
}

CUIManager::~CUIManager()
{
}

void CUIManager::Destroy()
{
	myUI.Destroy();
}

void CUIManager::Init(const std::string& aUIFilePath)
{
	JsonDocument menuJson;
	menuJson.LoadFile(aUIFilePath.c_str());

	myUI.Init(menuJson["element"]);
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
