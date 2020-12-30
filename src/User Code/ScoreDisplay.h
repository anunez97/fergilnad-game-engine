// Score Display

#ifndef _ScoreDisplay
#define _ScoreDisplay

#include "DisplayBase.h"

class ScoreDisplay : public DisplayBase
{
public:
	ScoreDisplay();
	ScoreDisplay(const ScoreDisplay& other) = delete;
	ScoreDisplay& operator=(const ScoreDisplay& other) = delete;
	~ScoreDisplay();

	void Initialize();
	void Render();
	void SetPosition(int x, int y);

	void SetScore(int score);
	

private:
	SpriteFont* pFont;
	SpriteString* pDisplay;

	int posx;
	int posy;

};

#endif _ScoreDisplay