// Octree Self Test Command

#ifndef _OctreeSelfTestCommand
#define _OctreeSelfTestCommand

#include "OctreeTestCommandBase.h"

class OctreeSelfTestCommand : public OctreeTestCommandBase
{
public:
	OctreeSelfTestCommand() = default;
	OctreeSelfTestCommand(const OctreeSelfTestCommand& other) = delete;
	OctreeSelfTestCommand& operator=(const OctreeSelfTestCommand& other) = delete;
	~OctreeSelfTestCommand();

	OctreeSelfTestCommand(CollisionDispatchBase* pd, int id);

	virtual void Execute();
	virtual void SetNode(OctreeNode* node);

private:
	CollisionDispatchBase* pDispatch;
	OctreeNode* pNode;

	int ID;
};

#endif _OctreeSelfTestCommand