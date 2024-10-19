// Collision Test Command Base

#ifndef _CollisionTestCommandBase
#define _CollisionTestCommandBase

#include "CollidableGroup.h"
#include "CollisionDispatchBase.h"

class CollisionTestCommandBase
{
public:
	CollisionTestCommandBase() {};
	CollisionTestCommandBase(const CollisionTestCommandBase& other) = delete;
	CollisionTestCommandBase& operator=(const CollisionTestCommandBase& other) = delete;
	virtual ~CollisionTestCommandBase() {};

	virtual void Execute() {};
};

#endif _CollisionTestCommandBase