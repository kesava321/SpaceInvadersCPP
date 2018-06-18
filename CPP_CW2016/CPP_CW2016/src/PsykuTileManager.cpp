#include "PsykuTileManager.h"

PsykuTileManager::PsykuTileManager() 
	: TileManager(50, 50)
{

}

PsykuTileManager::~PsykuTileManager() {

}

void PsykuTileManager::DrawTileAt(
	BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	unsigned int iColour = 0x001110 * ((iMapX + iMapY + GetValue(iMapX, iMapY)) % 16);
	pEngine->DrawRectangle(
		iStartPositionScreenX,
		iStartPositionScreenY,
		iStartPositionScreenX + GetTileWidth() - 1,
		iStartPositionScreenY + GetTileHeight() - 1,
		iColour,
		pSurface);
}

