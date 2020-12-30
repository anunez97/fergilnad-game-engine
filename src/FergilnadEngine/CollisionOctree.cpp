// Collision Octree

#include "CollisionOctree.h"
#include "VisualizerAttorney.h"
#include "CollidableAttorney.h"

CollisionOctree::CollisionOctree()
	:NUM_OBJS(0)
{
	pRoot = 0;
	PendingRebuild = false;
}

CollisionOctree::~CollisionOctree()
{
	delete pRoot;

	for (std::list<OctreeTestCommandBase*>::iterator it = colTestList.begin(); it != colTestList.end(); it++)
	{
		delete (*it);
	}
}

void CollisionOctree::CreateTree(int len, Vect origin)
{
	ORIGIN = origin;
	SIDE_LENGTH = static_cast<float>(len);
	float half = exp2(SIDE_LENGTH) / 2.0f;

	if (pRoot != 0)
		delete pRoot;

	pRoot = new OctreeNode(Vect(-half, -half, -half) + origin, Vect(half, half, half) + origin, 0);
}

void CollisionOctree::RebuildTree()
{
	if (!PendingRebuild)
		return;

	// doubles the size of the tree
	SIDE_LENGTH++;

	delete pRoot;

	float half = exp2(SIDE_LENGTH) / 2.0f;

	pRoot = new OctreeNode(Vect(-half, -half, -half) + ORIGIN, Vect(half, half, half) + ORIGIN, 0);

	// insert all objects in the tree
	for (std::list<Collidable*>::iterator it = objectList.begin(); it != objectList.end(); it++)
	{
		pendingQueue.push(*it);
	}

	objectList.clear();


	// add the collision tests to the tree
	for (std::list<OctreeTestCommandBase*>::iterator it = colTestList.begin(); it != colTestList.end(); it++)
	{
		pendingTestList.push(*it);
	}

	NUM_OBJS = 0;
	colTestList.clear();

	PendingRebuild = false;
}

void CollisionOctree::InsertObject(Collidable* col)
{
	pendingQueue.push(col);
}

void CollisionOctree::RemoveObject(Collidable* col)
{
	OctreeNode* node = CollidableAttorney::Octree::GetParentNode(col);

	node->RemoveObject(col);

	NUM_OBJS--;
	objectList.remove(col);
	DebugMsg::out("Removed an object from the tree:  %i objects left\n", NUM_OBJS);
}

void CollisionOctree::Render()
{
	pRoot->Render();
}

void CollisionOctree::ProcessTrimCommands()
{
	pRoot->TrimBranches();
}

void CollisionOctree::UpdateTree()
{
	RebuildTree();

	// Insert any pending objects
	while (pendingQueue.size() > 0)
	{
		pRoot->InsertObjQueue(pendingQueue.front());
		NUM_OBJS++;

		objectList.push_back(pendingQueue.front());
		pendingQueue.pop();

		DebugMsg::out("Inserted an object into tree: %i objects in the tree\n", NUM_OBJS);
	}

	// add any new test commands to the tree
	while (pendingTestList.size() > 0)
	{
		pRoot->AddCollisionTest(pendingTestList.front());
		colTestList.push_back(pendingTestList.front());

		pendingTestList.pop();
	}

	pRoot->Update();
}

void CollisionOctree::ProcessCollisions()
{
	pRoot->ProcessCollisions();
}

void CollisionOctree::AddTestCommand(OctreeTestCommandBase* cmd)
{
	pendingTestList.push(cmd);
}

void CollisionOctree::SubmitRebuild()
{
	PendingRebuild = true;
}

void CollisionOctree::ShowNode(Collidable* col)
{
	OctreeNode* node = CollidableAttorney::Octree::GetParentNode(col);
	node->RenderNode();
}