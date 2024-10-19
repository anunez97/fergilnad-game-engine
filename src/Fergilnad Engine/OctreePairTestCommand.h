// Octree Test Command

#ifndef _OctreePairTestCommand
#define _OctreePairTestCommand

#include "OctreeTestCommandBase.h"

class OctreePairTestCommand : public OctreeTestCommandBase
{
public:
	OctreePairTestCommand() = default;
	OctreePairTestCommand(const OctreePairTestCommand& other) = delete;
	OctreePairTestCommand& operator=(const OctreePairTestCommand& other) = delete;
	~OctreePairTestCommand();

	OctreePairTestCommand(CollisionDispatchBase* pd, int id1, int id2);

	virtual void Execute();
	virtual void SetNode(OctreeNode* node);

private:
	CollisionDispatchBase* pDispatch;
	OctreeNode* pNode;

	int ID1;
	int ID2;

};

#endif _OctreePairTestCommand