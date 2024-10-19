// Terrain Rectangle Area

#ifndef _TerrainRectangleArea
#define _TerrainRectangleArea

#include "AzulCore.h"

#include "CollisionVolumeAABB.h"

class Terrain;
class TRAIterator;

class TerrainRectangleArea
{
public:
	TerrainRectangleArea() = default;
	TerrainRectangleArea(const TerrainRectangleArea& other) = delete;
	TerrainRectangleArea& operator=(const TerrainRectangleArea& other) = delete;
	~TerrainRectangleArea();
	TerrainRectangleArea(Terrain* t, Vect min, Vect max);

	/// <summary>
	/// Gives an iterator for the first cell in the area
	/// </summary>
	/// <returns>Returns an iterator for the terrain area</returns>
	TRAIterator begin();
	/// <summary>
	/// Gives an iterator for the cell after the last cell in the area
	/// </summary>
	/// <returns>Returns an iterator for the terrain area</returns>
	TRAIterator end();
	/// <summary>
	/// Gives the iterator for the next iterator depending on the cell coordinates
	/// </summary>
	/// <param name="x">Column value for cell</param>
	/// <param name="z">Row value for the cell</param>
	/// <returns>Returns a pointer to an iterator for the terrain area</returns>
	TRAIterator* next(int x, int z);

	/// <summary>
	/// Gives the cell's AABB
	/// </summary>
	/// <param name="x">Column coordinate for the cell</param>
	/// <param name="z">Row coordinate for the cell</param>
	/// <returns>Returns the cell's AABB</returns>
	CollisionVolumeAABB GetCellAABB(int x, int z);

private:
	Terrain* pTerrain;
	int colmin;
	int rowmin;
	int colmax;
	int rowmax;

};

#endif _TerrainRectangleArea