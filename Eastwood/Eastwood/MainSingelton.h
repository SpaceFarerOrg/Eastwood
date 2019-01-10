#pragma once

class CRenderer;
class CDebugDrawer;

class CMainSingleton
{
public:
	static CMainSingleton& GetInstance();
	
	static CRenderer& GetRenderer();
	static CDebugDrawer& GetDebugDrawer();

private:
	CMainSingleton();

	CRenderer* myRenderer;
	CDebugDrawer* myDebugDrawer;
};