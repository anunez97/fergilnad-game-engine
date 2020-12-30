// Collision Test Seld Command

#include "CollisionTestSelfCommand.h"
#include "CollisionVolumeBSphere.h"
#include "CollidableAttorney.h"
#include "FGNMathTools.h"
#include "VisualizerAttorney.h"

CollisionTestSelfCommand::CollisionTestSelfCommand(CollidableGroup* g, CollisionDispatchBase* pd)
	:pG1(g), pDispatch(pd)
{
}

CollisionTestSelfCommand::~CollisionTestSelfCommand()
{
	delete pDispatch;
}

void CollisionTestSelfCommand::Execute()
{
	const CollidableGroup::CollidableCollection& Collection1 = pG1->GetColliderCollection();

	for (auto it1 = Collection1.begin(); it1 != Collection1.end(); it1++)
	{
		auto tmpit = it1;

		for (auto it2 = ++tmpit; it2 != Collection1.end(); it2++)
		{
			// Check if Collidables' BSpheres intersect
			if (FGNMathTools::Intersect(CollidableAttorney::Volume::GetCollisionBSphere(*it1), CollidableAttorney::Volume::GetCollisionBSphere(*it2)))
			{
				VisualizerAttorney::Show::BSphere(CollidableAttorney::Volume::GetCollisionBSphere(*it1), Color::Purple);
				VisualizerAttorney::Show::BSphere(CollidableAttorney::Volume::GetCollisionBSphere(*it2), Color::Purple);

				const CollisionVolume& cv1 = CollidableAttorney::Volume::GetCollisionVolume((*it1));
				const CollisionVolume& cv2 = CollidableAttorney::Volume::GetCollisionVolume((*it2));

				// Check if Collidables' selected collision volumes intersect
				if (FGNMathTools::Intersect(cv1, cv2))
				{
					Visualizer::ShowCollisionVolume(cv1, Color::Red);
					Visualizer::ShowCollisionVolume(cv2, Color::Red);

					pDispatch->ProcessCallbacks(*it1, *it2);
				}
				else
				{
					Visualizer::ShowCollisionVolume(cv1, Color::Blue);
					Visualizer::ShowCollisionVolume(cv2, Color::Blue);
				}
			}
			else
			{
				VisualizerAttorney::Show::BSphere(CollidableAttorney::Volume::GetCollisionBSphere(*it1), Color::Green);
				VisualizerAttorney::Show::BSphere(CollidableAttorney::Volume::GetCollisionBSphere(*it2), Color::Green);
			}
		}
	}
}