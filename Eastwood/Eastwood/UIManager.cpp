#include "UIManager.h"
#include "Graphics/RenderWindow.hpp"
#include "UISprite.h"

#include "JsonDocument.h"
#include "InputManager.h"

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
	myFilePath = aUIFilePath;
	JsonDocument menuJson;
	menuJson.LoadFile(aUIFilePath.c_str());

	myUI.SetUIManager(this);
	myUI.Init(menuJson["element"]);
}

void CUIManager::Update(float dt)
{
	myEvents.clear();

	myUI.Update();

	if (CInputManager::GetInstance().IsKeyPressed(EKeyCode::F5))
	{
		Destroy();
		Init(myFilePath);
	}
}

void CUIManager::Render(sf::RenderWindow* aRenderWindow)
{
	myUI.Render(aRenderWindow);
}

void CUIManager::RegisterEvent(const std::string & aEventName)
{
	myEvents.insert(aEventName);
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
