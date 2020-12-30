// Objective Display

#ifndef _ObjectiveDisplay
#define _ObjectiveDisplay

#include "DisplayBase.h"

class ObjectiveDisplay : public DisplayBase
{
public:
	ObjectiveDisplay();
	ObjectiveDisplay(const ObjectiveDisplay& other) = delete;
	ObjectiveDisplay&operator=(const ObjectiveDisplay& other) = delete;
	~ObjectiveDisplay();

	void Initialize();
	void Render();
	void SetPosition(int x, int y);

	int GetHeight();

private:
	SpriteFont* pFont;
	SpriteString* pDisplay;

	int posx;
	int posy;

};

#endif _ObjectiveDisplay