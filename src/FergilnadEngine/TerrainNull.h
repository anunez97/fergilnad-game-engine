// Terrain Null

#ifndef _TerrainNull
#define _TerrainNull

#include "Terrain.h"

class TerrainNull : public Terrain
{
public:
	TerrainNull() {};
	TerrainNull(const TerrainNull& other) = delete;
	TerrainNull&operator=(const TerrainNull& other) = delete;
	~TerrainNull() {};

	void Render(Camera*) {};
};

#endif _TerrainNull