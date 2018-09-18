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

	void Init(/*Json file later*/);
	void Update(float dt);
	void Render(sf::RenderWindow* aRenderWindow);

	bool CheckForEvent(const std::string& aEventName);

private:
	std::unordered_set<std::string> myEvents;
	CUIElement myUI;
};