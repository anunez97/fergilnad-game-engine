// Terrain Manager Attorney

#ifndef _TerrainManagerAttorney
#define _TerrainManagerAttorney

#include "TerrainManager.h"

class TerrainManagerAttorney
{
	friend class Fergilnad;

	static void Delete() { TerrainManager::Delete(); }
};

#endif _TerrainManagerAttorney