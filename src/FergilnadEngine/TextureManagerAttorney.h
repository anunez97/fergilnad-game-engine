// Texture Manager Attorney

#ifndef _TextureManagerAttorney
#define _TextureManagerAttorney

#include "TextureManager.h"

class TextureManagerAttorney
{
	friend class Fergilnad;

private:
	static void Delete() { TextureManager::Delete(); }
};

#endif _TextureManagerAttorney