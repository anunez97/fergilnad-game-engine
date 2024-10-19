// Octree Test Command Base

#ifndef _OctreeTestCommandBase
#define _OctreeTestCommandBase

#include "CollisionTestCommandBase.h"

class OctreeNode;

class OctreeTestCommandBase : public CollisionTestCommandBase
{
public:
	OctreeTestCommandBase() {};
	OctreeTestCommandBase(const OctreeTestCommandBase& other) = delete;
	OctreeTestCommandBase& operator=(const OctreeTestCommandBase& other) = delete;
	~OctreeTestCommandBase() {};

	virtual void Execute() {};
	virtual void SetNode(OctreeNode*) {};

};

#endif _OctreeTestCommandBase