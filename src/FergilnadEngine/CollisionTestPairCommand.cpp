// Collision Test Pair Command

#include "CollisionTestPairCommand.h"
#include "CollisionVolumeBSphere.h"
#include "CollidableAttorney.h"
#include "FGNMathTools.h"
#include "VisualizerAttorney.h"

CollisionTestPairCommand::CollisionTestPairCommand(CollidableGroup* g1, CollidableGroup* g2, CollisionDispatchBase* pd)
	:pG1(g1), pG2(g2), pDispatch(pd)
{
}

CollisionTestPairCommand::~CollisionTestPairCommand()
{
	delete pDispatch;
}

void CollisionTestPairCommand::Execute()
{
	// Get Collider Collections for both groups
	const CollidableGroup::CollidableCollection& Collection1 = pG1->GetColliderCollection();
	const CollidableGroup::CollidableCollection& Collection2 = pG2->GetColliderCollection();

	// Check if both groups' AABBs intersect
	if (FGNMathTools::Intersect(*pG1->GetAABB(), *pG2->GetAABB()))
	{
		for (auto it1 = Collection1.begin(); it1 != Collection1.end(); it1++)
		{
			// Check if the Collidable's BSphere intersects with the second group's AABB
			if (FGNMathTools::Intersect(CollidableAttorney::Volume::GetCollisionBSphere(*it1), *pG2->GetAABB()))
			{
				//VisualizerAttorney::Show::BSphere(CollidableAttorney::Volume::GetCollisionBSphere(*it1), Color::Green);

				for (auto it2 = Collection2.begin(); it2 != Collection2.end(); it2++)
				{
					// Check if Collidable in group 1's BSphere intersects with Collidable in group 2's Bsphere 
					if (FGNMathTools::Intersect(CollidableAttorney::Volume::GetCollisionBSphere(*it1), CollidableAttorney::Volume::GetCollisionBSphere(*it2)))
					{
						//VisualizerAttorney::Show::BSphere(CollidableAttorney::Volume::GetCollisionBSphere(*it1), Color::Green);
						//VisualizerAttorney::Show::BSphere(CollidableAttorney::Volume::GetCollisionBSphere(*it2), Color::Green);

						const CollisionVolume& cv1 = CollidableAttorney::Volume::GetCollisionVolume(*it1);
						const CollisionVolume& cv2 = CollidableAttorney::Volume::GetCollisionVolume(*it2);

						// Check if Collidable's selected collision volumes intersect with each other
						if (FGNMathTools::Intersect(cv1, cv2))
						{
							pDispatch->ProcessCallbacks(*it1, *it2);

							Visualizer::ShowCollisionVolume(cv1, Color::Purple);
							Visualizer::ShowCollisionVolume(cv2, Color::Purple);
						}
						else
						{
							Visualizer::ShowCollisionVolume(cv1, Color::Yellow);
							Visualizer::ShowCollisionVolume(cv2, Color::Yellow);
						}
					}
					else
					{
						//VisualizerAttorney::Show::BSphere(CollidableAttorney::Volume::GetCollisionBSphere(*it2), Color::Orange);
						//VisualizerAttorney::Show::BSphere(CollidableAttorney::Volume::GetCollisionBSphere(*it2), Color::Orange);
					}
				}
			}
			else
			{
				//VisualizerAttorney::Show::BSphere(CollidableAttorney::Volume::GetCollisionBSphere(*it1), Color::Orange);
			}
		}

		//VisualizerAttorney::Show::AABB(*pG1->GetAABB(), Color::Red);
		//VisualizerAttorney::Show::AABB(*pG2->GetAABB(), Color::Red);
	}
	else
	{
		//VisualizerAttorney::Show::AABB(*pG1->GetAABB(), Color::Blue);
		//VisualizerAttorney::Show::AABB(*pG2->GetAABB(), Color::Blue);
	}
	
}