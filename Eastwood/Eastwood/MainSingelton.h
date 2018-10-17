#pragma once

class CRenderer;

class CMainSingleton
{
public:
	static CMainSingleton& GetInstance();
	
	static CRenderer& GetRenderer();
private:
	CMainSingleton();

	CRenderer* myRenderer;
};