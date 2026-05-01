//
//  game.c
//  June Endstrasser
//	May 2026
//  Defines logic for the main puzzle screen game state

#include <stdlib.h>
#include "game.h"


static const int screenW = 400, screenH = 240;


//// game state

//player
LCDSprite *player = NULL;
int playerSize = 0;


// background
LCDSprite *bgSprite = NULL;
LCDBitmap *bgImage = NULL;

// cached images


void setPDPtr(PlaydateAPI* p) {
	pd = p;
	graphics = pd->graphics;
	sound = pd->sound;
	sprites = pd->sprite;
	sys = pd->system;
}


LCDBitmap *loadImageAtPath(const char *path)
{
	const char *outErr = NULL;
	LCDBitmap *img = pd->graphics->loadBitmap(path, &outErr);
	if ( outErr != NULL ) {
		pd->system->logToConsole("Error loading image at path '%s': %s", path, outErr);
	}
	return img;
}



// -- Background Sprite -- //

static void drawBackgroundSprite(LCDSprite* sprite, PDRect bounds, PDRect drawrect)
{
	pd->graphics->drawBitmap(bgImage, 0, 0, 0);
	//pd->graphics->drawBitmap(bgImage, 0, bgY-bgH, 0);
}

static void setupBackground(void)
{
	bgSprite = pd->sprite->newSprite();

	bgImage = loadImageAtPath("images/pieceandboardBG");
	//pd->graphics->getBitmapData(bgImage, NULL, &bgH, NULL, NULL, NULL);

	//pd->sprite->setUpdateFunction(bgSprite, updateBackgroundSprite);
	pd->sprite->setDrawFunction(bgSprite, drawBackgroundSprite);

	PDRect bgBounds = PDRectMake(0, 0, screenW, screenH);
	pd->sprite->setBounds(bgSprite, bgBounds);

	pd->sprite->setZIndex(bgSprite, 0);

	pd->sprite->addSprite(bgSprite);
}


static SpriteCollisionResponseType playerCollisionResponse(LCDSprite* sprite, LCDSprite* other)
{
	return kCollisionTypeOverlap;
}

//player nextposition is at the sprite's top left
//returns true if the next position is within bounds, otherwise false.
bool playerBoundsCheck(int nextX, int nextY)
{
	if (nextX < 0 || //left
		nextX > screenW || //right
		nextY < 0 || //top
		nextY > screenH) //botom
	{
		return false;
	}
	else
		return true;
}

static void updatePlayer(LCDSprite* s)
{
	PDButtons current;
	pd->system->getButtonState(&current, NULL, NULL);

	int dx = 0;
	int dy = 0;

	if ( current & kButtonUp ) {
		dy = -4;
	} else if ( current & kButtonDown ) {
		dy = 4;
	}
	if ( current & kButtonLeft ) {
		dx = -4;
	} else if ( current & kButtonRight ) {
		dx = 4;
	}

	float x, y;
	pd->sprite->getPosition(s, &x, &y);

	if (playerBoundsCheck(x + dx, y + dy))
		pd->sprite->moveBy(s, dx, dy);

}

LCDSprite* CreateSpriteFromImage(int posX, int posY, const char* path, float centerX, float centerY)
{
	//alloc sprite
	LCDSprite* newSpr = pd->sprite->newSprite();

	//set the image
	LCDBitmap* sprImage = loadImageAtPath(path);
	int w, h;
	pd->graphics->getBitmapData(sprImage, &w, &h, NULL, NULL, NULL);
	pd->sprite->setImage(newSpr, sprImage, kBitmapUnflipped);

	//make the bounding box
	PDRect cr = PDRectMake(0, 0, w, h);
	pd->sprite->setCollideRect(newSpr, cr);
	sprites->setCenter(newSpr, centerX, centerY);

	//move to position
	pd->sprite->moveTo(newSpr, centerX, centerY);

	//add sprite to scene
	pd->sprite->addSprite(newSpr);

	return newSpr;
}

static LCDSprite* createPlayer(int centerX, int centerY)
{
	LCDSprite *cursorSpr = pd->sprite->newSprite();

	pd->sprite->setUpdateFunction(cursorSpr, updatePlayer);

	LCDBitmap *sprImage = loadImageAtPath("images/arrowCursor");
	int w, h;
	pd->graphics->getBitmapData(sprImage, &w, &h, NULL, NULL, NULL);
	
	if (w != h)
	{
		pd->system->error("player sprite is not square!");
	}
	playerSize = w;

	pd->sprite->setImage(cursorSpr, sprImage, kBitmapUnflipped);

	PDRect cr = PDRectMake(5, 5, w, h);
	pd->sprite->setCollideRect(cursorSpr, cr);
	pd->sprite->setCollisionResponseFunction(cursorSpr, playerCollisionResponse);

	pd->sprite->moveTo(cursorSpr, centerX, centerY);

	pd->sprite->setZIndex(cursorSpr, 1000);
	pd->sprite->addSprite(cursorSpr);

	//pd->sprite->setTag(plane, kPlayer);

	//backgroundPlaneCount += 1;

	return cursorSpr;
}


// game initialization
void setupGame(void)
{
	srand(pd->system->getSecondsSinceEpoch(NULL));

	setupBackground();
	player = createPlayer(200, 180);
	//preloadImages();
}

// cranking the crank changes the maximum number of enemy planes allowed
void checkCrank(void)
{
	/*float change = pd->system->getCrankChange();

	if ( change > 1 ) {
		maxEnemies += 1;
		if ( maxEnemies > 119 ) { maxEnemies = 119; }
		pd->system->logToConsole("Maximum number of enemy planes: %d", maxEnemies);
	} else if ( change < -1 ) {
		maxEnemies -= 1;
		if ( maxEnemies < 0 ) { maxEnemies = 0; }
		pd->system->logToConsole("Maximum number of enemy planes: %d", maxEnemies);
	}*/
}


void checkButtons(void)
{
	PDButtons pushed;
	pd->system->getButtonState(NULL, &pushed, NULL);

	if ( pushed & kButtonA)
	{
		//playerFire();
	}
}


// main update function
int update(void* ud)
{
	checkButtons();
	checkCrank();

	/*spawnEnemyIfNeeded();
	spawnBackgroundPlaneIfNeeded();*/

	pd->sprite->updateAndDrawSprites();
	

	return 1;
}
