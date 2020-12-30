// Sprite Font Manager Attorney

#ifndef _SpriteFontManagerAttorney
#define _SpriteFontManagerAttorney

#include "SpriteFontManager.h"

class SpriteFontManagerAttorney
{
	friend class Fergilnad;

	static void Delete() { SpriteFontManager::Delete(); }
};

#endif _SpriteFontManagerAttorney