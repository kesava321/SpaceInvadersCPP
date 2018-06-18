#pragma once
#include "header.h"
#include "TileManager.h"



class PsykuTileManager : public TileManager
{
public:
	PsykuTileManager();
	~PsykuTileManager();

	void DrawTileAt(
		BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const;

};