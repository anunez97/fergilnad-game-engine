// Display Base

#ifndef _DisplayBase
#define _DisplayBase

#include "SpriteString.h"
#include "SpriteFont.h"

class DisplayBase
{
public:
	DisplayBase() {};
	DisplayBase(const DisplayBase& other) = delete;
	DisplayBase& operator=(const DisplayBase& other) = delete;
	~DisplayBase() {};

	virtual void Initialize() = 0;
	virtual void Render() = 0;
	virtual void SetPosition(int x, int y) = 0;
};

#endif _DisplayBase