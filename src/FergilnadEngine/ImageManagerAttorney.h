// Image Manager Attorney

#ifndef _ImageManagerAttorney
#define _ImageManagerAttorney

#include "ImageManager.h"

class ImageManagerAttorney
{
	friend class Fergilnad;

private:
	static void Delete() { ImageManager::Delete(); }
};

#endif _ImageManagerAttorney