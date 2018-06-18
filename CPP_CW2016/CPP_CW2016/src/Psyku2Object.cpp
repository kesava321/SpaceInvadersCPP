#include "header.h"

#include "PsykuEngine.h"
#include "Psyku2Object.h"
#include <iostream>
#include <vector>


Psyku2Object::Psyku2Object(PsykuEngine* pEngine, int iMapX, int iMapY)
	: DisplayableObject(pEngine)
	, m_pMainEngine(pEngine)
	, m_iMapX(iMapX)
	, m_iMapY(iMapY)
	, m_iDir(0)
{
	// The square coordinate will be the centre of the square.
	// Because we start drawing half the size to the top-left.
	m_iStartDrawPosX = -25;
	m_iStartDrawPosY = -25;

	// Record the square size as both height and width
	m_iDrawWidth = 50;
	m_iDrawHeight = 50;

	// Out item at specific coordinates
	m_iPreviousScreenX = m_iCurrentScreenX = iMapX * 50 + 25 + 25;
	m_iPreviousScreenY = m_iCurrentScreenY = iMapY * 50 + 25 + 40;
	

	// And make it visible
	SetVisible(true);
}

Psyku2Object::~Psyku2Object(void)
{
}



void Psyku2Object::Draw()
{
	// Do not draw if it should not be visible
	if (!IsVisible())
		return;

	int iSize = 25;
	//	int iTick = m_pMainEngine->GetTime()/20; // 1 per 20ms
	//	int iFrame = iTick % 30;
	//	int iSize = 10 + iFrame;
	//	if ( iFrame > 15 )
	//		iSize = 10 + (30-iFrame);

	m_pMainEngine->DrawScreenRectangle(
		m_iCurrentScreenX - iSize,
		m_iCurrentScreenY - iSize,
		m_iCurrentScreenX + iSize - 1,
		m_iCurrentScreenY + iSize - 1,
		0x00ff0f);
	
	
	

	// Store the position at which the object was last drawn
	// You MUST do this to ensure that the screen is updated when only drawing movable objects
	// This tells the system where to 'undraw' the object from
	StoreLastScreenPositionForUndraw();
}

void Psyku2Object::DoUpdate(int iCurrentTime)
{
	m_iPreviousScreenX = m_iCurrentScreenX;
	m_iPreviousScreenY = m_iCurrentScreenY;


	// If movement has finished
	if (m_oMover.HasMovementFinished(iCurrentTime))
	{
		PsykuTileManager& tm = m_pMainEngine->GetTileManager();

		

		// Set off a new movement
		switch (rand() % 30)
		{
		case 0: // Increase dir by 1
			m_iDir = (m_iDir + 5) % 4;
			break;
		case 1: // Reduce dir by 1
			m_iDir = (m_iDir + 3) % 4;
			break;

		}

		// Allow some control over the object by the player
		if (m_pMainEngine->IsKeyPressed(SDLK_UP))
			m_iDir = 0;
		if (m_pMainEngine->IsKeyPressed(SDLK_RIGHT))
			m_iDir = 1;
		if (m_pMainEngine->IsKeyPressed(SDLK_DOWN))
			m_iDir = 2;
		if (m_pMainEngine->IsKeyPressed(SDLK_LEFT))
			m_iDir = 3;



		if (m_iMapX + GetXDiffForDirection(m_iDir) > 14)
			m_iDir = 3;
		if (m_iMapX + GetXDiffForDirection(m_iDir) < 0)
			m_iDir = 1;
		if (m_iMapY + GetYDiffForDirection(m_iDir) > 10)
			m_iDir = 0;
		if (m_iMapY + GetYDiffForDirection(m_iDir) < 0)
			m_iDir = 2;

		

		// Allow move - set up new movement now
		m_iMapX += GetXDiffForDirection(m_iDir);
		m_iMapY += GetYDiffForDirection(m_iDir);

		m_oMover.Setup(
			m_iCurrentScreenX,
			m_iCurrentScreenY,
			m_iMapX * 50 + 25 + 25,
			m_iMapY * 50 + 25 + 40,
			iCurrentTime,
			iCurrentTime + 300 + rand() % 50);
		
	}

	// If making a move then do the move
	if (!m_oMover.HasMovementFinished(iCurrentTime))
	{
		// Ask the mover where the object should be
		m_oMover.Calculate(iCurrentTime);
		m_iCurrentScreenX = m_oMover.GetX();
		m_iCurrentScreenY = m_oMover.GetY();
	}


	
	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();

	}



