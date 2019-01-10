#include "MainSingelton.h"

#include "Renderer.h"
#include "DebugDrawer.h"

CMainSingleton::CMainSingleton()
{
	myRenderer = new CRenderer();
	myDebugDrawer = new CDebugDrawer();
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

CDebugDrawer & CMainSingleton::GetDebugDrawer()
{
	return *(GetInstance().myDebugDrawer);
}

