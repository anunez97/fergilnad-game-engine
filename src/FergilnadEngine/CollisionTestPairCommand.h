// Collision Test Pair Command

#ifndef _CollisionTestPairCommand
#define _CollisionTestPairCommand

#include "CollisionTestCommandBase.h"

class CollisionTestPairCommand : public CollisionTestCommandBase
{
public:
	CollisionTestPairCommand() = default;
	CollisionTestPairCommand(const CollisionTestPairCommand& other) = delete;
	CollisionTestPairCommand& operator=(const CollisionTestPairCommand& other) = delete;
	~CollisionTestPairCommand();

	CollisionTestPairCommand(CollidableGroup* g1, CollidableGroup* g2, CollisionDispatchBase* pd);

	virtual void Execute();

private:
	CollidableGroup* pG1;
	CollidableGroup* pG2;
	CollisionDispatchBase* pDispatch;

};

#endif _CollisionTestPairCommand