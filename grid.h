//
//  grid.h
//  June Endstrasser
//	May 2026
//

#ifndef grid_h
#define grid_h

#include <stdio.h>

#ifndef PD_API_INCLUDED 
#include "pd_api.h"  
#define PD_API_INCLUDED  
#endif


typedef struct Cell {
	int ID;
	bool isActive;
	LCDSprite* sprite;
}Cell;

void GridInit();
void GridUpdate();
void GridDestroy();

#endif 
