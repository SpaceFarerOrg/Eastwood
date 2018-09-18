#pragma once
#include <unordered_map>

class CUIManager
{
public:
	CUIManager();
	~CUIManager();

	void Init();
	void Update(float dt);
	void Render();

private:
	std::vector<std::string> myEvents;
};