#include "header.h"

#include "PsykuEngine.h"
#include "Psyku1Object.h"
#include <math.h>
#include <iostream>

Psyku1Object::Psyku1Object(PsykuEngine* pEngine, int iMapX, int iMapY)
	: DisplayableObject(pEngine)
	, m_pMainEngine(pEngine)
	, m_iMapX(iMapX)
	, m_iMapY(iMapY)
	, m_iDir(0)
{
	// The ball coordinate will be the centre of the ball
	// Because we start drawing half the size to the top-left.
	m_iStartDrawPosX = -25;
	m_iStartDrawPosY = -25;
	theta = (double)(rand() % 628) / 100.0;
	std::cout << theta << "\n";
	

	// Record the ball size as both height and width
	m_iDrawWidth = 50;
	m_iDrawHeight = 50;

	// Out item at specific coordinates
	m_iPreviousScreenX = m_iCurrentScreenX = iMapX * 50 + 25 + 25;
	m_iPreviousScreenY = m_iCurrentScreenY = iMapY * 50 + 25 + 40;

	// And make it visible
	SetVisible(true);
}

Psyku1Object::~Psyku1Object(void)
{
}

void Psyku1Object::Draw()
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

	m_pMainEngine->DrawScreenOval(
		m_iCurrentScreenX - iSize,
		m_iCurrentScreenY - iSize,
		m_iCurrentScreenX + iSize - 1,
		m_iCurrentScreenY + iSize - 1,
		0xff0000);

	// Store the position at which the object was last drawn
	// You MUST do this to ensure that the screen is updated when only drawing movable objects
	// This tells the system where to 'undraw' the object from
	StoreLastScreenPositionForUndraw();
}

void Psyku1Object::DoUpdate(int iCurrentTime)
{
	m_iPreviousScreenX = m_iCurrentScreenX;
	m_iPreviousScreenY = m_iCurrentScreenY;


	// If movement has finished
	if (m_oMover.HasMovementFinished(iCurrentTime))
	{
		PsykuTileManager& tm = m_pMainEngine->GetTileManager();
		theta += 0.1;
		int centreX = 25;
		int centreY = 25;
		// Allow move - set up new movement now
		m_iMapX = 5*cos(theta) + 5;
		m_iMapY = 5*sin(theta) + 5;

		m_oMover.Setup(
			m_iCurrentScreenX,
			m_iCurrentScreenY,
			m_iMapX * 50 + 25 + 25,
			m_iMapY * 50 + 25 + 40,
			iCurrentTime,
			iCurrentTime + 400 + rand() % 200);
		// END OF REPLACE THE FOLLOWING CODE FOR CHANGE B
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
};