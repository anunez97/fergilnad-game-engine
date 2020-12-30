// TRA Iterator

#include "TRAIterator.h"
#include "TerrainRectangleArea.h"

TRAIterator::TRAIterator(const TRAIterator& other)
{
	this->pTerrainArea = other.pTerrainArea;
	this->x = other.x;
	this->z = other.z;
}

TRAIterator& TRAIterator::operator=(const TRAIterator& other)
{
	this->pTerrainArea = other.pTerrainArea;
	this->x = other.x;
	this->z = other.z;

	return *this;
}

TRAIterator::~TRAIterator()
{
}

bool TRAIterator::operator!=(const TRAIterator& other)
{
	if (this->pTerrainArea == other.pTerrainArea)
	{
		if (this->x == other.x && this->z == other.z)
			return false;
	}
	
	return true;
}

TRAIterator& TRAIterator::operator++()
{
	// get the next cell in the area
	TRAIterator* tmp = pTerrainArea->next(x, z);

	this->x = tmp->x;
	this->z = tmp->z;

	delete tmp;

	return *this;
}

TRAIterator::TRAIterator(TerrainRectangleArea* area, int x, int z)
	:pTerrainArea(area), x(x), z(z)
{
}

CollisionVolumeAABB TRAIterator::CellAABB()
{
	return pTerrainArea->GetCellAABB(x, z);
}