// Collidable Group

#include "CollidableGroup.h"
#include "CollisionVolumeAABB.h"
#include "CollidableAttorney.h"

CollidableGroup::CollidableGroup()
{
	pAABB = new CollisionVolumeAABB();
}

CollidableGroup::~CollidableGroup()
{
	delete pAABB;
}

void CollidableGroup::Register(Collidable* c, CollidableCollectionRef& ref)
{
	pAABB->ComputeData(&CollidableAttorney::Volume::GetCollisionBSphere(c));

	ref = CollideCol.insert(CollideCol.end(), c);
}

void CollidableGroup::Deregister(const CollidableCollectionRef& ref)
{
	CollideCol.erase(ref);
}

const CollidableGroup::CollidableCollection& CollidableGroup::GetColliderCollection()
{
	return CollideCol;
}

const CollisionVolumeAABB* CollidableGroup::GetAABB()
{
	return pAABB;
}

void CollidableGroup::UpdateGroupAABB()
{
	if (CollideCol.size() == 0)
	{
		pAABB->Reset();
		return;
	}

	pAABB->SetInitialSphere(&CollidableAttorney::Volume::GetCollisionBSphere(*CollideCol.begin()));

	for (CollidableCollection::iterator it = ++CollideCol.begin(); it != CollideCol.end(); it++)
	{	
		pAABB->ComputeData(&CollidableAttorney::Volume::GetCollisionBSphere(*it));
	}
}