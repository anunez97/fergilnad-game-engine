// Collision Manager

#include "CollisionManager.h"
#include "CollidableGroup.h"
#include "CollisionOctree.h"
#include "OctreeNode.h"

CollisionManager::FGNTypeID CollisionManager::TypeIDNextNumber = 0;

CollisionManager::CollisionManager()
{
	Octree = new CollisionOctree();

	// The collision area is created by default in case user doesn't define one
	Octree->CreateTree(10, Vect(0, 0, 0));
}

CollisionManager::~CollisionManager()
{
	delete Octree;

	for (size_t i = 0; i < ColGroupCollection.size(); i++)
	{
		delete ColGroupCollection[i];
	}

	while(colTestCommands.size() > 0)
	{
		delete colTestCommands.front();
		colTestCommands.pop_front();
	}
}

void CollisionManager::SetGroupForTypeID(FGNTypeID ind)
{

	if (ColGroupCollection.size() < size_t(ind + 1))
		ColGroupCollection.resize(ind + 1);

	if (ColGroupCollection[ind] == nullptr)
		ColGroupCollection[ind] = new CollidableGroup();
}

CollidableGroup* CollisionManager::GetColGroup(FGNTypeID id)
{
	return ColGroupCollection[id];
}

void CollisionManager::ProcessCollisions()
{
	//*
	Octree->ProcessTrimCommands();

	Octree->UpdateTree();

	Octree->ProcessCollisions();

	Octree->Render(); // for debugging
	//*/

	//* the only commands being execute by the collision manager are for terrain collision
	for (CollisionTestCommands::iterator it = colTestCommands.begin(); it != colTestCommands.end(); it++)
	{
		(*it)->Execute();
	}

	for (CollidableGroupCollection::iterator it = ColGroupCollection.begin(); it != ColGroupCollection.end(); it++)
	{
		(*it)->UpdateGroupAABB();
	}
	//*/
}

/* ---- Used for Collision Octree Project ---- */
void CollisionManager::InsertInTree(Collidable* col)
{
	Octree->InsertObject(col);
}

void CollisionManager::RemoveFromTree(Collidable* col)
{
	Octree->RemoveObject(col);
}

void CollisionManager::SetCollisionArea(int size, Vect origin)
{
	Octree->CreateTree(size, origin);
}

void CollisionManager::RebuildTree()
{
	Octree->SubmitRebuild();
}

void CollisionManager::ShowNode(Collidable* col)
{
	Octree->ShowNode(col);
}