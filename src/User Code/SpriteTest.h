// Sprite Test

#ifndef _SpriteTest
#define _SpriteTest

#include "GameObject.h"

class FergilnadSprite;
class SpriteFont;
class SpriteString;
class ScoreDisplay;

class SpriteTest : public GameObject
{
public:
	SpriteTest();
	SpriteTest(const SpriteTest& other) = delete;
	SpriteTest& operator=(const SpriteTest& other) = delete;
	~SpriteTest();

	virtual void Draw2D();
	virtual void KeyPressed(AZUL_KEY k);

private:
	FergilnadSprite* pTest;
	SpriteFont* fonttest;
	SpriteFont* fonttest2;
	SpriteString* ss;
	ScoreDisplay* sd;
};

#endif _SpriteTest