// Collision Manager

#ifndef _CollisionManager
#define _CollisionManager

#include "AzulCore.h"
#include "CollisionDispatch.h"
#include "CollisionTestPairCommand.h"
#include "CollisionTestSelfCommand.h"
#include "CollisionTestTerrain.h"
#include <vector>
#include <list>

/* ---- Collision Octree ---- */
#include "OctreePairTestCommand.h"
#include "OctreeSelfTestCommand.h"
#include "CollisionOctree.h"
#include "OctreeNode.h"

class CollidableGroup;
class CollisionTestCommandBase;
class CollisionOctree;
class Collidable;

class OctreeDispatchBase;
class OctreeNode;

class CollisionManager
{
public:
	using FGNTypeID = int;
	static const FGNTypeID FGN_UNDEFINED = -1;

private:
	static FGNTypeID TypeIDNextNumber;

	using CollidableGroupCollection = std::vector<CollidableGroup*>;
	CollidableGroupCollection ColGroupCollection;

	void SetGroupForTypeID(FGNTypeID ind);

	using CollisionTestCommands = std::list<CollisionTestCommandBase*>;
	CollisionTestCommands colTestCommands;

	/* ---- Used for collision octree ---- */
	CollisionOctree* Octree;
	

public:
	CollisionManager();
	CollisionManager(const CollisionManager& other) = delete;
	CollisionManager& operator=(const CollisionManager& other) = delete;
	~CollisionManager();

	template <typename C>
	FGNTypeID GetTypeID()
	{
		static FGNTypeID TypeID = TypeIDNextNumber++;

		DebugMsg::out("Type ID: %i\n", TypeID);

		SetGroupForTypeID(TypeID);
		
		return TypeID;
	}

	CollidableGroup* GetColGroup(FGNTypeID id);

	/// <summary>
	/// Sets the Collidable to check for collisions against Collidables of the same type (two instances of the same type)
	/// </summary>
	template<typename C>
	void SetCollisionSelf()
	{
		//CollidableGroup* pG = ColGroupCollection[GetTypeID<C>()];

		//CollisionDispatch<C, C>* pDispatch = new CollisionDispatch<C, C>();

		//colTestCommands.push_back(new CollisionTestSelfCommand(pG, pDispatch));

		/* ---- for collision octree ---- */
		CollisionDispatch<C, C>* pD = new CollisionDispatch<C, C>();

		Octree->AddTestCommand(new OctreeSelfTestCommand(pD, GetTypeID<C>()));
	}

	/// <summary>
	/// Sets the Collidable to check for collisions against a different type (enemy against a bullet)
	/// </summary>
	template<typename C1, typename C2>
	void SetCollisionPair()
	{
		//CollidableGroup* pG1 = ColGroupCollection[GetTypeID<C1>()];
		//CollidableGroup* pG2 = ColGroupCollection[GetTypeID<C2>()];

		//CollisionDispatch<C1, C2>* pDispatch = new CollisionDispatch<C1, C2>();

		//colTestCommands.push_back(new CollisionTestPairCommand(pG1, pG2, pDispatch));

		/* ---- for collision octree ---- */
		CollisionDispatch<C1, C2>* pD = new CollisionDispatch<C1, C2>();

		Octree->AddTestCommand(new OctreePairTestCommand(pD, GetTypeID<C1>(), GetTypeID<C2>()));
	}

	/// <summary>
	/// Sets the Collidable to check for collisions against the scene's terrain
	/// </summary>
	template<typename C>
	void SetCollisionTerrain()
	{
		CollidableGroup* pG = ColGroupCollection[GetTypeID<C>()];

		colTestCommands.push_back(new CollisionTestTerrain(pG));
	}

	/// <summary>
	/// Processes any collision tests the collision manager may have.  Only processes terrain collisions
	/// </summary>
	void ProcessCollisions();

	/* ---- Used for Collision Octree ---- */

	/// <summary>
	/// Sets the area that the collision octree will encompass
	/// </summary>
	/// <param name="size">The side length of the octree will be a power of 2; 2^length</param>
	/// <param name="origin">The center of octree</param>
	void SetCollisionArea(int size, Vect origin);

	/// <summary>
	/// Inserts a Collidable into the octree
	/// </summary>
	/// <param name="col">Pointer to the Collidable</param>
	void InsertInTree(Collidable* col);

	/// <summary>
	/// Removes a Collidable from the octree
	/// </summary>
	/// <param name="col">Pointer to the Collidable</param>
	void RemoveFromTree(Collidable* col);

	/// <summary>
	/// Sets the octree to be rebuilt in the next frame
	/// </summary>
	void RebuildTree();

	/// <summary>
	/// Renders the bounding area of the node the Collidable is in
	/// </summary>
	/// <param name="col">Pointer to the Collidable</param>
	void ShowNode(Collidable* col);

};

#endif _CollisionManager