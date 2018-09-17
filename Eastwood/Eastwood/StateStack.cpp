#include "StateStack.h"

#include "State.h"


CStateStack::CStateStack()
{
}


CStateStack::~CStateStack()
{
}

void CStateStack::Init(short aMaxSize)
{
	myStates.reserve(aMaxSize);
	myMaxSize = aMaxSize;
}

void CStateStack::Update(float dt)
{
	if (myStates.size() > 0)
	{
		myStates[myCurrentStateIndex]->Update(dt);
	}
}

void CStateStack::Render(sf::RenderWindow * aRenderWindow)
{
	if (myStates.size() > 0)
	{
		myStates[myCurrentStateIndex]->Render(aRenderWindow);
	}
}

void CStateStack::Push(CState * aNewState)
{
	if (myStates.size() < myMaxSize)
	{
		myCurrentStateIndex = myStates.size();
		myStates.push_back(aNewState);
		aNewState->SetOwner(this);
		aNewState->Init();
	}
}

bool CStateStack::Pop()
{
	if (myStates.size() > 0)
	{
		delete myStates[myCurrentStateIndex];

		myStates.pop_back();
		myCurrentStateIndex--;
		return true;
	}
	return false;
}

void CStateStack::PopAll()
{
	if (myStates.size() > 0)
	{
		for (CState*& state : myStates)
		{
			delete state;
		}

		myStates.clear();
	}
}

short CStateStack::Size()
{
	return myStates.size();
}
