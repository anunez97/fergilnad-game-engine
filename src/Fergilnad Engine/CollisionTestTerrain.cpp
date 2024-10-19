// Collision Test Terrain

#include "CollisionTestTerrain.h"
#include "SceneManager.h"
#include "Terrain.h"
#include "CollidableAttorney.h"
#include "FGNMathTools.h"
#include "VisualizerAttorney.h"
#include "TerrainRectangleArea.h"
#include "TRAIterator.h"

CollisionTestTerrain::~CollisionTestTerrain()
{
}

CollisionTestTerrain::CollisionTestTerrain(CollidableGroup* g)
	:pG1(g)
{
}

void CollisionTestTerrain::Execute()
{
	const CollidableGroup::CollidableCollection& Collection = pG1->GetColliderCollection();
	Terrain* pTerrain = SceneManager::GetTerrain();

	Vect center;
	float radius;

	Vect max;
	Vect min;

	for (auto it = Collection.begin(); it != Collection.end(); it++)
	{
		center = CollidableAttorney::Volume::GetCollisionBSphere(*it).GetCenter();
		radius = CollidableAttorney::Volume::GetCollisionBSphere(*it).GetRadius();

		max.set(center + Vect(radius, radius, radius));
		min.set(center - Vect(radius, radius, radius));

		TerrainRectangleArea CandidateCells(pTerrain, min, max);

		for (TRAIterator itCell = CandidateCells.begin(); itCell != CandidateCells.end(); ++itCell)
		{
			if (FGNMathTools::Intersect(itCell.CellAABB(), CollidableAttorney::Volume::GetCollisionBSphere(*it)))
			{
				CollidableAttorney::Volume::GetCollisionVolume(*it).DebugView(Color::Black);

				// check if objects collision volume intersects with the cell
				if (FGNMathTools::Intersect(CollidableAttorney::Volume::GetCollisionVolume(*it), itCell.CellAABB()))
				{
					VisualizerAttorney::Show::AABB(itCell.CellAABB(), Color::Red);
					(*it)->CollisionTerrain();
				}
			}
		}
	}
}