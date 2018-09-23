#pragma once
#include <unordered_set>
#include "UIElement.h"

namespace sf
{
	class RenderWindow;
}

class CUIManager
{
public:
	CUIManager();
	~CUIManager();

	void Destroy();

	void Init(const std::string& aUIFilePath);
	void Update(float dt);
	void Render(sf::RenderWindow* aRenderWindow);

	void RegisterEvent(const std::string& aEventName);
	bool CheckForEvent(const std::string& aEventName);

	template<typename T>
	T* GetElement(const std::string& aElementName);

private:
	std::unordered_set<std::string> myEvents;
	CUIElement myUI;
	std::string myFilePath;
};

template<typename T>
inline T * CUIManager::GetElement(const std::string & aElementName)
{
	return myUI.FindElement<T>(aElementName);
}
