#include "header.h"
#include "PsykuEngine.h"
#include "Psyku1Object.h"
#include "Psyku2Object.h"



PsykuEngine::PsykuEngine()
	: BaseEngine(6)
{
}


PsykuEngine::~PsykuEngine()
{
}


void PsykuEngine::SetupBackgroundBuffer() {
	FillBackground(0x80FF80);

	// Specify how many tiles wide and high
	tileManager.SetSize(12, 20);
	// Set up the tiles
	for (int x = 0; x < 12; x++)
		for (int y = 0; y < 20; y++)
			tileManager.SetValue(x, y, rand() % 31);
	// Specify the screen x,y of top left corner
	tileManager.SetBaseTilesPositionOnScreen(25, 40);
	// Tell it to draw tiles from x1,y1 to x2,y2 in tile array,
	// to the background of this screen
	tileManager.DrawAllTiles(this, this->GetBackground(), 0, 0, 10, 6);

	DrawBackgroundVerticalSidedRegion(530, 620, // X
		80, 50, // Top line
		230, 280, // Bottom line
		0xfff000);

	int iLineThickness = 2;

	// Draw a triangle where all three points are specified.
	DrawBackgroundTriangle(150, 150, 150, 250, 300, 300, 0xf0ff0f);
	DrawBackgroundTriangle(200, 400, 200, 450, 400, 400, 0xf0ff0f);
	DrawBackgroundTriangle(470, 250, 450, 475, 400, 500, 0xf0ff0f);

	DrawBackgroundString(150, 500, "draw to background", 0xff00ff, NULL);
}



int PsykuEngine::InitialiseObjects()
{
	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	DrawableObjectsChanged();

	// Destroy any existing objects
	DestroyOldObjects();

	// Creates an array one element larger than the number of objects that you want.
	CreateObjectArray(11);

	// You MUST set the array entry after the last one that you create to NULL, so that the system knows when to stop.
	
	StoreObjectInArray(0, new Psyku1Object(this, 1, 1));
	StoreObjectInArray(1, new Psyku1Object(this, 9, 9));
	StoreObjectInArray(2, new Psyku1Object(this, 13, 9));
	StoreObjectInArray(3, new Psyku1Object(this, 9, 5));
	StoreObjectInArray(4, new Psyku1Object(this, 13, 5));
	StoreObjectInArray(5, new Psyku2Object(this, 2, 2));
	StoreObjectInArray(6, new Psyku2Object(this, 10, 10));
	StoreObjectInArray(7, new Psyku2Object(this, 14, 10));
	StoreObjectInArray(8, new Psyku2Object(this, 10, 6));
	StoreObjectInArray(9, new Psyku2Object(this, 14, 6)); 

	// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in order to work out where the end of the array is.
	StoreObjectInArray(10, NULL);

	// NOTE: We also need to destroy the objects, but the method at the 
	// top of this function will destroy all objects pointed at by the 
	// array elements so we can ignore that here.

	return 0;

}

/* Draw text labels */
void PsykuEngine::DrawStrings()
{
	CopyBackgroundPixels(0/*X*/, 0/*Y*/, GetScreenWidth(), 30/*Height*/);
	DrawScreenString(150, 50, "Kesava Text On Background", 0xff00ff, NULL);
}

/* Draw any string which should appear on top of moving objects - i.e. objects move behind these */
void PsykuEngine::DrawStringsOnTop()
{
	// Build the string to print
	char buf[128];
	CopyBackgroundPixels(0/*X*/, 0/*Y*/, GetScreenWidth(), 30/*Height*/); 
	sprintf(buf, "Time %6d", rand(), rand());
	DrawScreenString(150, 8, buf, 0xff00ff, NULL);
	DrawScreenString(150, 80, "On top of the objects", 0xff00ff, NULL);
}


/* Overridden GameAction to ensure that objects use the modified time */
void PsykuEngine::GameAction()
{
	// If too early to act then do nothing
	if (!IsTimeToAct()) // No sleep, will just keep polling constantly - this is a difference from the base class
		return;

	// Don't act for another 1 tick - this is a difference from the base class
	SetTimeToAct(1);

	UpdateAllObjects(GetTime());
}


// Override to add a node at specified point
void PsykuEngine::MouseDown(int iButton, int iX, int iY)
{
}

/*
Handle any key presses here.
Note that the objects themselves (e.g. player) may also check whether a key is pressed
*/
void PsykuEngine::KeyDown(int iKeyCode)
{
	switch (iKeyCode)
	{
	case SDLK_ESCAPE: // End program when escape is pressed
		SetExitWithCode(0);
		break;
	case SDLK_SPACE: // SPACE Pauses
		break;
	}
}

