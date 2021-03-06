// Octree Test Command

#include "OctreeSelfTestCommand.h"

#include "OctreeNodeAttorney.h"
#include "CollidableAttorney.h"
#include "FGNMathTools.h"
#include "VisualizerAttorney.h"

OctreeSelfTestCommand::OctreeSelfTestCommand(CollisionDispatchBase* pd, int id)
	:pDispatch(pd), ID(id)
{
}

OctreeSelfTestCommand::~OctreeSelfTestCommand()
{
	delete pDispatch;
}

void OctreeSelfTestCommand::SetNode(OctreeNode* node)
{
	pNode = node;
}

void OctreeSelfTestCommand::Execute()
{
	OctreeNode::ObjectList objectList = OctreeNodeAttorney::CollisionTest::GetObjectList(pNode);
	// there are no objects to test
	if (objectList.size() == 0)
		return;

	OctreeNode::ObjectList::iterator it = objectList.begin();
	OctreeNode::ObjectList parentObjectList = OctreeNodeAttorney::CollisionTest::GetParentObjectList(pNode);
	//for (ObjectList::iterator it = objectList.begin(); it != objectList.end(); it++)
	while (it != objectList.end())
	{
		auto tmp = it;
		// test this node's objects against each other
		for (OctreeNode::ObjectList::iterator it2 = ++tmp; it2 != objectList.end(); it2++)
		{
			Collidable* C1;
			Collidable* C2;

			int id1 = CollidableAttorney::Octree::GetTypeID(*it);
			int id2 = CollidableAttorney::Octree::GetTypeID(*it2);

			// check if the ids match the ids that are being tested for
			if (id1 == ID && id2 == ID)
			{
				C1 = *it;
				C2 = *it2;
			}
			// If the ids do not match do not try any collision tests and move on 
			else
				continue;

			const CollisionVolumeBSphere& bs1 = CollidableAttorney::Volume::GetCollisionBSphere(C1);
			const CollisionVolumeBSphere& bs2 = CollidableAttorney::Volume::GetCollisionBSphere(C2);

			if (FGNMathTools::Intersect(bs1, bs2))
			{
				VisualizerAttorney::Show::BSphere(bs1, Color::Purple);
				VisualizerAttorney::Show::BSphere(bs2, Color::Purple);

				const CollisionVolume& cv1 = CollidableAttorney::Volume::GetCollisionVolume(C1);
				const CollisionVolume& cv2 = CollidableAttorney::Volume::GetCollisionVolume(C2);

				// Do collision test
				if (FGNMathTools::Intersect(cv1, cv2))
				{
					Visualizer::ShowCollisionVolume(cv1, Color::Red);
					Visualizer::ShowCollisionVolume(cv2, Color::Red);

					pDispatch->ProcessCallbacks(C1, C2);
				}
				else
				{
					Visualizer::ShowCollisionVolume(cv1, Color::Blue);
					Visualizer::ShowCollisionVolume(cv2, Color::Blue);
				}
			}
			else
			{
				VisualizerAttorney::Show::BSphere(bs1, Color::Green);
				VisualizerAttorney::Show::BSphere(bs2, Color::Green);
			}
		}

		// test the objects from the parent nodes against this nodes objects
		for (OctreeNode::ObjectList::iterator it3 = parentObjectList.begin(); it3 != parentObjectList.end(); it3++)
		{
			Collidable* C1;
			Collidable* C2;

			int id1 = CollidableAttorney::Octree::GetTypeID(*it);
			int id2 = CollidableAttorney::Octree::GetTypeID(*it3);

			// check if the ids match the ids that are being tested for
			if (id1 == ID && id2 == ID)
			{
				C1 = *it;
				C2 = *it3;
			}
			// If the ids do not match do not try any collision tests and move on 
			else
				continue;

			const CollisionVolumeBSphere& bs1 = CollidableAttorney::Volume::GetCollisionBSphere(C1);
			const CollisionVolumeBSphere& bs2 = CollidableAttorney::Volume::GetCollisionBSphere(C2);

			if (FGNMathTools::Intersect(bs1, bs2))
			{
				VisualizerAttorney::Show::BSphere(bs1, Color::Purple);
				VisualizerAttorney::Show::BSphere(bs2, Color::Purple);

				const CollisionVolume& cv1 = CollidableAttorney::Volume::GetCollisionVolume(C1);
				const CollisionVolume& cv2 = CollidableAttorney::Volume::GetCollisionVolume(C2);

				// Do collision test
				if (FGNMathTools::Intersect(cv1, cv2))
				{
					Visualizer::ShowCollisionVolume(cv1, Color::Red);
					Visualizer::ShowCollisionVolume(cv2, Color::Red);

					pDispatch->ProcessCallbacks(C1, C2);

				}
				else
				{
					Visualizer::ShowCollisionVolume(cv1, Color::Blue);
					Visualizer::ShowCollisionVolume(cv2, Color::Blue);
				}
			}
			else
			{
				VisualizerAttorney::Show::BSphere(bs1, Color::Green);
				VisualizerAttorney::Show::BSphere(bs2, Color::Green);
			}
		}

		it++;
	}
}