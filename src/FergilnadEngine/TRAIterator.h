// TRA Iterator

#ifndef _TRAIterator
#define _TRAIterator

#include "Terrain.h"
#include "CollisionVolumeAABB.h"

class CollisionVolumeAABB;
class TerrainRectangleArea;

class TRAIterator
{
public:
	TRAIterator() = default;
	TRAIterator(const TRAIterator& other);
	TRAIterator& operator=(const TRAIterator& other);
	TRAIterator& operator++();
	bool operator!=(const TRAIterator&);
	~TRAIterator();

	TRAIterator(TerrainRectangleArea* area, int x, int z);

	/// <summary>
	/// Gives an AABB based on the cell the iterator refers to
	/// </summary>
	/// <returns>AABB that belongs to the cell the iterator refers to </returns>
	CollisionVolumeAABB CellAABB();

private:
	TerrainRectangleArea* pTerrainArea;
	int x;
	int z;
};

#endif _TRAIterator