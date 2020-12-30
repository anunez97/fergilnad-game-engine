// Reload Display

#ifndef _ReloadDisplay
#define _ReloadDisplay

#include "DisplayBase.h"

class ReloadDisplay : public DisplayBase
{
public:
	ReloadDisplay();
	ReloadDisplay(const ReloadDisplay& other) = delete;
	ReloadDisplay& operator=(const ReloadDisplay& other) = delete;
	~ReloadDisplay();

	void Initialize();
	void Render();
	void SetPosition(int x, int y);

	void Reloading();
	void ReadyToFire();
	void UpdateDisplay();

	

private:
	SpriteFont* pFont;
	SpriteString* pDisplay;

	int posx;
	int posy;
};

#endif _ReloadDisplay