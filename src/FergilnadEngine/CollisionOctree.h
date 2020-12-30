// Collision Octree

#ifndef _CollisionOctree
#define _CollisionOctree

#include "OctreeNode.h"
#include <queue>

class Collidable;
class OctreeTestCommandBase;

class CollisionOctree
{
public:
	CollisionOctree();
	CollisionOctree(const CollisionOctree& other) = delete;
	CollisionOctree& operator=(const CollisionOctree& other) = delete;
	~CollisionOctree();

	/// <summary>
	/// Creates the initial octree
	/// </summary>
	/// <param name="len">The sidelength of the octree; sidelength = 2^length</param>
	/// <param name="origin">The center of the octree</param>
	void CreateTree(int len, Vect origin);

	/// <summary>
	/// Rebuilds the octree; deletes the old tree and creates a new one.  Only gets called when an object is out of bounds of the tree
	/// </summary>
	void RebuildTree();

	/// <summary>
	/// Inserts a Collidable into the tree
	/// </summary>
	/// <param name="col">Pointer to the Collidable</param>
	void InsertObject(Collidable* col);

	/// <summary>
	/// Removes a Collidable from the tree
	/// </summary>
	/// <param name="col">Pointer to the Collidable</param>
	void RemoveObject(Collidable* col);

	/// <summary>
	/// Used for debugging. Renders all the nodes of the octree. Blue nodes have no objects in them, while red nodes have at least one object in them.
	/// </summary>
	void Render();

	/// <summary>
	/// Processes any branch trim commands. Deletes any unused tree branches
	/// </summary>
	void ProcessTrimCommands();

	/// <summary>
	/// Updates the octree
	/// </summary>
	void UpdateTree();

	/// <summary>
	/// Process the collisions in the octree
	/// </summary>
	void ProcessCollisions();

	/// <summary>
	/// Add a new collision test to the octree
	/// </summary>
	/// <param name="cmd">Pointer to the new collision test command</param>
	void AddTestCommand(OctreeTestCommandBase* cmd);

	/// <summary>
	/// Sets the octree to be rebuilt in the next frame
	/// </summary>
	void SubmitRebuild();

	/// <summary>
	/// Renders the node that the Collidable is inside of
	/// </summary>
	/// <param name="col">Pointer to the Collidable</param>
	void ShowNode(Collidable* col);

private:
	Vect ORIGIN;
	std::queue<Collidable*> pendingQueue;
	std::queue<OctreeTestCommandBase*> pendingTestList;
	std::list<OctreeTestCommandBase*> colTestList;
	std::list<Collidable*> objectList;

	OctreeNode* pRoot;

	float SIDE_LENGTH;

	int NUM_OBJS;
	bool PendingRebuild;
};

#endif _CollisionOctree