// Collidable Group

#ifndef _CollidableGroup
#define _CollidableGroup

#include <list>

class Collidable;
class CollisionVolumeAABB;

class CollidableGroup
{
public:
	using CollidableCollection = std::list<Collidable*>;

private:
	CollidableCollection CollideCol;
	CollisionVolumeAABB* pAABB;

public:
	CollidableGroup();
	CollidableGroup(const CollidableGroup& other) = delete;
	CollidableGroup& operator=(const CollidableGroup& other) = delete;
	~CollidableGroup();

	using CollidableCollectionRef = CollidableCollection::iterator;

	void Register(Collidable* c, CollidableCollectionRef& ref);
	void Deregister(const CollidableCollectionRef& ref);
	const CollidableCollection& GetColliderCollection();
	const CollisionVolumeAABB* GetAABB();

	void UpdateGroupAABB();
};

#endif _CollidableGroup