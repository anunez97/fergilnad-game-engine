// Collision Test Terrain

#ifndef _CollisionTestTerrain
#define _CollisionTestTerrain

#include "CollisionTestCommandBase.h"

class CollisionTestTerrain : public CollisionTestCommandBase
{
public:
	CollisionTestTerrain() = default;
	CollisionTestTerrain(const CollisionTestTerrain& other) = delete;
	CollisionTestTerrain&operator=(const CollisionTestTerrain& other) = delete;
	~CollisionTestTerrain();

	CollisionTestTerrain(CollidableGroup* g);

	virtual void Execute();

private:
	CollidableGroup* pG1;

};

#endif _CollisionTestTerrain