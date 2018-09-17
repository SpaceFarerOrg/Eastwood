#pragma once

namespace sf
{
	class RenderWindow;
}

class CStateStack;

class CState
{
public:
	CState();
	~CState();

	void SetOwner(CStateStack* aOwner);

	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(sf::RenderWindow* aRenderWindow) = 0;

protected:
	void Pop();
	void PopAll();

	void Push(CState* aNewState);

private:
	CStateStack* myOwner;
};

