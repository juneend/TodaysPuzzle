//
//  game.h
//  Extension OS X
//
//  Created by Dan Messing on 1/26/18.
//  Copyright © 2018 Panic, Inc. All rights reserved.
//

#ifndef game_h
#define game_h

#include <stdio.h>

#ifndef PD_API_INCLUDED 
#define PD_API_INCLUDED  
	#include "pd_api.h"
#endif

#ifndef GRID_INCLUDED
#define GRID_INCLUDED
	#include "grid.h"
#endif

extern const PlaydateAPI* pd;
extern const struct playdate_graphics* graphics;
extern const struct playdate_sound* sound;
extern const struct playdate_sprite* sprites;
extern const struct playdate_sys* sys;

//utility functions
//TODO: move these to their own util file maybe?
LCDBitmap* loadImageAtPath(const char* path);
LCDSprite* CreateSpriteFromImage(int posX, int posY, const char* path, float centerX, float centerY);

int update(void* ud);
void setPDPtr(PlaydateAPI* p);
void setupGame(void);

#endif /* game_h */
