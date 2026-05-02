//
//  grid.h
//  June Endstrasser
//	May 2026
//  Defines logic for a grid, made up of cells, that comprise the calendar board.

#include "grid.h"


#include "game.h"

static LCDSprite* cell;


void CellPlayerCollision(int ID)
{
	Cell* data = sprites->getUserdata(cell);
	data->isActive = true;
	sys->logToConsole("cell active!");
}

void GridInit()
{
	//create cell data
	Cell* newCell = sys->realloc(NULL, sizeof(Cell));

	newCell->ID = 0;
	newCell->isActive = false;

	//create sprite and set the data to this cell
	LCDSprite* cellSpr = CreateSpriteFromImage(50, 50, "images/cells/jan", 0, 0);
	sprites->setTag(cellSpr, TAG_CELL);
	sprites->setUserdata(cellSpr, newCell);

	cell = cellSpr;

}


void GridUpdate(bool playerUpdate)
{
	Cell* data = sprites->getUserdata(cell);
	data->isActive = false;
	sys->logToConsole("cell inactive!");
}

void GridDestroy()
{
	//free cell data
	sys->realloc(sprites->getUserdata(cell), 0);
	//free sprite
	sprites->freeSprite(cell);
	
}
