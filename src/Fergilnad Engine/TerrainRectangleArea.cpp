// Terrain Rectangle Area

#include "TerrainRectangleArea.h"
#include "TRAIterator.h"
#include "Terrain.h"

TerrainRectangleArea::TerrainRectangleArea(Terrain* t, Vect _min, Vect _max)
	:pTerrain(t)
{
	Terrain::Cell min = pTerrain->GetCell(_min);
	Terrain::Cell max = pTerrain->GetCell(_max);

	// index of the first cell in the area
	colmin = min.x;
	rowmin = min.z;

	// index of the last cell
	colmax = max.x;
	rowmax = max.z;
}

TerrainRectangleArea::~TerrainRectangleArea()
{
}

TRAIterator TerrainRectangleArea::begin()
{
	return TRAIterator(this, colmin, rowmin);
}

TRAIterator TerrainRectangleArea::end()
{
	// returns an out of bounds iterator
	return TRAIterator(this, colmax + 1, rowmax - 1);
}

TRAIterator* TerrainRectangleArea::next(int x, int z)
{
	int tmpx = x + 1;
	int tmpz = z;
	// end of a row
	if (tmpx > colmax)
	{
		tmpx = colmin;
		tmpz--;
	}

	// past the range of the area
	if (tmpz < rowmax)
	{
		return new TRAIterator(this, colmax + 1, rowmax - 1);
	}

	return new TRAIterator(this, tmpx, tmpz);
}

CollisionVolumeAABB TerrainRectangleArea::GetCellAABB(int x, int z)
{
	return CollisionVolumeAABB(pTerrain->GetCellMin(Terrain::Cell(x, z)), pTerrain->GetCellMax(Terrain::Cell(x, z)));
}