#include "MainSingelton.h"

#include "Renderer.h"

CMainSingleton::CMainSingleton()
{
	myRenderer = new CRenderer(*this);
}

CMainSingleton & CMainSingleton::GetInstance()
{
	static CMainSingleton instance;

	return instance;
}

CRenderer & CMainSingleton::GetRenderer()
{
	return *(GetInstance().myRenderer);
}

