// Radar Display

#ifndef _RadarDisplay
#define _RadarDisplay

#include "DisplayBase.h"

class RadarDisplay : public DisplayBase
{
public:
	RadarDisplay();
	RadarDisplay(const RadarDisplay& other) = delete;
	RadarDisplay& operator=(const RadarDisplay& other) = delete;
	~RadarDisplay();

	void Initialize();
	void Render();
	void SetPosition(int x, int y);

private:
	SpriteFont* pFont;
	SpriteString* pDisplay;

	int posx;
	int posy;
};

#endif _RadarDisplay