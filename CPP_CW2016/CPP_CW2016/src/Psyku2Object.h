#pragma once
#include "displayableobject.h"
#include "MovementPosition.h"
#include "PsykuEngine.h"

class Psyku2Object;

class Psyku2Object :
	public DisplayableObject

{

public:
	Psyku2Object(PsykuEngine* pEngine, int iMapX, int iMapY);
	~Psyku2Object(void);

	void Draw();
	void DoUpdate(int iCurrentTime);


	int GetXDiffForDirection(int iDir)
	{
		switch (iDir % 4)
		{
		case 0: return 0; // Up
		case 1: return 1; // Right
		case 2: return 0; // Down
		case 3: return -1; // Left
		default: return 0; // Can never happen
		}
	}

	int GetYDiffForDirection(int iDir)
	{
		switch (iDir % 4)
		{
		case 0: return -1; // Up
		case 1: return 0; // Right
		case 2: return 1; // Down
		case 3: return 0; // Left
		default: return 0; // Can never happen
		}
	}

private:
	PsykuEngine* m_pMainEngine;
	MovementPosition m_oMover;
	double theta;

	int m_iMapX;
	int m_iMapY;
	int m_iDir;


};