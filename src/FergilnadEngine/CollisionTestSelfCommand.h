// Collision Test Self Command

#ifndef _CollisionTestSelfCommand
#define _CollisionTestSelfCommand

#include "CollisionTestCommandBase.h"

class CollisionTestSelfCommand : public CollisionTestCommandBase
{
public:
	CollisionTestSelfCommand() = default;
	CollisionTestSelfCommand(const CollisionTestSelfCommand& other) = delete;
	CollisionTestSelfCommand& operator=(const CollisionTestSelfCommand& other) = delete;
	~CollisionTestSelfCommand();

	CollisionTestSelfCommand(CollidableGroup* g, CollisionDispatchBase* pd);

	virtual void Execute();

private:
	CollidableGroup* pG1;
	CollisionDispatchBase* pDispatch;
	
};

#endif _CollisionTestSelfCommand