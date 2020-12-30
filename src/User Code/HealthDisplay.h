// Health Display

#ifndef _HealthDisplay
#define _HealthDisplay

#include "DisplayBase.h"

class HealthDisplay : public DisplayBase
{
public:
	HealthDisplay();
	HealthDisplay(const HealthDisplay& other) = delete;
	HealthDisplay& operator=(const HealthDisplay& other) = delete;
	~HealthDisplay();

	void Initialize();
	void Render();
	void SetPosition(int x, int y);

	int GetWidth();
	int GetHeight();

private:
	SpriteFont* pFont;
	SpriteString* pDisplay;

	int posx;
	int posy;

};

#endif _HealthDisplay