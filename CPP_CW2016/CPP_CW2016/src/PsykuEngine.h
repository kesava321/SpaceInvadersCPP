#pragma once
#include "PsykuTileManager.h"
#include "BaseEngine.h"


class PsykuEngine :
	public BaseEngine
{
public:
	PsykuEngine();
	~PsykuEngine();

	void SetupBackgroundBuffer();
	int InitialiseObjects();
	void DrawStrings();
	void GameAction();
	void MouseDown(int iButton, int iX, int iY);
	void KeyDown(int iKeyCode);
	void DrawStringsOnTop(); 
	// Get a reference to the current tile manager
	PsykuTileManager& GetTileManager() { return tileManager; }
private:
	PsykuTileManager tileManager;
};

