// Octree Node Attorney

#ifndef _OctreeNodeAttorney
#define _OctreeNodeAttorney

#include "OctreeNode.h"

class OctreeNodeAttorney
{
public:
	class CollisionTest
	{
		friend class OctreePairTestCommand;
		friend class CollisionOctree;
		friend class OctreeSelfTestCommand;

		static OctreeNode::ObjectList GetObjectList(OctreeNode* node) { return node->objectList; }
		static OctreeNode::ObjectList GetParentObjectList(OctreeNode* node) { return node->parentObjectList; }
	};
};

#endif _OctreeNodeAttorney