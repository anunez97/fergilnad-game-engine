// Reticle Display

#ifndef _ReticleDisplay
#define _ReticleDisplay

#include "DisplayBase.h"

class ReticleDisplay : public DisplayBase
{
public:
	ReticleDisplay();
	ReticleDisplay(const ReticleDisplay& other) = delete;
	ReticleDisplay&operator=(const ReticleDisplay& other) = delete;
	~ReticleDisplay();

	void Initialize();
	void Render();
	void SetPosition(int x, int y);

private:
	SpriteFont* pFont;
	SpriteString* pDisplay;

	int posx;
	int posy;

};

#endif _ReticleDisplay