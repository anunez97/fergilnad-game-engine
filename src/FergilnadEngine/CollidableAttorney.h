// Collidable Attorney

#ifndef _CollidableAttorney
#define _CollidableAttorney

#include "Collidable.h"

class CollidableAttorney
{
public:
	class SceneRegistration
	{
		friend class CollisionRegistrationCommand;
		friend class CollisionDeregistrationCommand;

		static void Register(Collidable* col) { col->SceneRegistration(); }
		static void Deregister(Collidable* col) { col->SceneDeregistration(); }
	};

public:
	class Volume
	{
		friend class CollidableGroup;
		friend class CollisionTestPairCommand;
		friend class CollisionTestSelfCommand;
		friend class CollisionTestTerrain;
		friend class Terrain;
		friend class OctreeNode;
		friend class OctreePairTestCommand;
		friend class OctreeSelfTestCommand;

		static const CollisionVolume& GetCollisionVolume(Collidable* col) { return col->GetCollisionVolume(); }
		static const CollisionVolumeBSphere& GetCollisionBSphere(Collidable* col) { return *col->GetCollisionSphere(); }
	};

public:
	class Octree
	{
		friend class OctreeNode;
		friend class CollisionOctree;
		friend class OctreePairTestCommand;
		friend class OctreeSelfTestCommand;

		static const void SetParentNode(Collidable* col, OctreeNode* parent) { col->SetParentNode(parent); }
		static OctreeNode* GetParentNode(Collidable* col) { return col->GetParentNode(); }
		static void RemoveFromTree(Collidable* col) { col->RemoveFromOctree(); }
		static int GetTypeID(Collidable* col) { return col->myID; }
	};
};

#endif _CollidableAttorney