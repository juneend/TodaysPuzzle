//
//  grid.h
//  June Endstrasser
//	May 2026
//  Defines logic for a grid, made up of cells, that comprise the calendar board.

#include "grid.h"


#include "game.h"

static Cell* cellptr;

void GridInit()
{
	Cell* newCell = sys->realloc(NULL, sizeof(Cell));

	newCell->ID = 0;
	newCell->isActive = false;

	LCDSprite* cellSpr = CreateSpriteFromImage(50, 50, "images/cells/jan", 0, 0);
	newCell->sprite = cellSpr;

	cellptr = newCell;

}

void GridUpdate()
{}

void GridDestroy()
{
	sprites->freeSprite(cellptr->sprite);
	sys->realloc(cellptr, 0);
	
}
