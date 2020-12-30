// Level Complete Display

#ifndef _LevelCompleteDisplay
#define _LevelCompleteDisplay

#include "GameObject.h"

class SpriteFont;
class SpriteString;

class LevelCompleteDisplay : public GameObject
{
public:
	LevelCompleteDisplay();
	LevelCompleteDisplay(const LevelCompleteDisplay& other) = delete;
	LevelCompleteDisplay& operator=(const LevelCompleteDisplay& other) = delete;
	~LevelCompleteDisplay();

	virtual void Draw2D();

private:
	SpriteFont* pFont;
	SpriteString* pDisplay;

	int posx;
	int posy;

};

#endif _LevelCompleteDisplay