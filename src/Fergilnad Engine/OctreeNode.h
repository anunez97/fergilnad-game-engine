// Octree Node

#ifndef _OctreeNode
#define _OctreeNode

#include "AzulCore.h"
#include <list>
#include <queue>

class Collidable;
class TrimBranchCommand;
class OctreeTestCommandBase;

class OctreeNode
{
	friend class OctreeNodeAttorney;

public:
	OctreeNode() = default;
	OctreeNode(const OctreeNode& other) = delete;
	OctreeNode& operator=(const OctreeNode& other) = delete;
	~OctreeNode();

	struct BoundingArea
	{
		void set(Vect _min, Vect _max)
		{
			min = _min;
			max = _max;
		}

		Vect min;
		Vect max;
	};

	

	using ObjectList = std::list<Collidable*>;
	using ObjectListRef = ObjectList::iterator;

	

private:
	// Min/Max for the Node's AABB
	BoundingArea boundingArea;

	OctreeNode* pParent;
	OctreeNode** ChildrenList;
	BoundingArea ChildrenBoundingAreas[8];

	ObjectList objectList;
	ObjectList parentObjectList;

	using TrimList = std::list<TrimBranchCommand*>;
	TrimList trimCmdList;

	using CollisionTestList = std::list<OctreeTestCommandBase*>;
	CollisionTestList colTestList;

	using CollidableQueue = std::queue<Collidable*>;
	CollidableQueue objRemoveQueue;
	CollidableQueue objInsertQueue;

	TrimBranchCommand* pTrimCommand;

	const float MIN_LENGTH;
	const int DeleteTimerReset;

	int NODE_INDEX;
	int DeleteTimer;
	const int MAX_CHILD_COUNT = 8;

	bool TREE_BUILT;
	bool TREE_READY;

public:
	OctreeNode(Vect min, Vect max, OctreeNode* parent);
	OctreeNode(BoundingArea area, OctreeNode* parent, int index);

	/// <summary>
	/// Creates a new OctreeNode
	/// </summary>
	/// <param name="area">The bounding area for the new node</param>
	/// <param name="index">The node's index</param>
	/// <returns> A new OctreeNode with the given bounding area and index</returns>
	OctreeNode* CreateNode(BoundingArea area, int index);

	/// <summary>
	/// Updates the node
	/// </summary>
	void Update();

	/// <summary>
	/// Updates the subtree starting at the node
	/// </summary>
	void UpdateTree();

	/// <summary>
	/// Removes a Collidable from the node
	/// </summary>
	/// <param name="col">Pointer to the Collidable</param>
	void RemoveObject(Collidable* col);

	/// <summary>
	/// Submits the node to be trimmed. Sent to parent node.
	/// </summary>
	void SubmitTrim();

	/// <summary>
	/// The node processes any trim commands it may have
	/// </summary>
	void TrimBranches();

	/// <summary>
	/// Renders the node along with all of its child nodes
	/// </summary>
	void Render(); // for debugging

	/// <summary>
	/// Renders just the node
	/// </summary>
	void RenderNode();
	
	/// <summary>
	/// Attempts to create a subtree starting at the node
	/// </summary>
	void BuildTree();
	
	/// <summary>
	/// Process any collision tests the node may have
	/// </summary>
	void ProcessCollisions();

	/// <summary>
	/// Adds a collision test command to the node
	/// </summary>
	/// <param name="command">Pointer to the test command</param>
	void AddCollisionTest(OctreeTestCommandBase* command);

	/// <summary>
	/// Checks whether a Collidable is contained within the bounding area
	/// </summary>
	/// <param name="col">Pointer to the Collidable</param>
	/// <param name="area">The bounding area that the Collidable will be tested against</param>
	/// <returns>True or false</returns>
	bool FitsInArea(Collidable* col, BoundingArea area);

	/// <summary>
	/// Checks whether the node has any child nodes
	/// </summary>
	/// <returns>True or false depending if there is a child node</returns>
	bool CheckForChildren();

	/// <summary>
	/// Inserts a Collidable into the node
	/// </summary>
	/// <param name="col"></param>
	void Insert(Collidable* col);

	/// <summary>
	/// Sets the bounding areas for any potential child nodes
	/// </summary>
	void CalculateChildAreas();

	/// <summary>
	/// Inserts a Collidable into the node's insert queue
	/// </summary>
	/// <param name="col"></param>
	void InsertObjQueue(Collidable* col);

	/// <summary>
	/// Sends a Collidable to the node to be tested for collisions
	/// </summary>
	/// <param name="col">Pointer to the Collidable to be sent</param>
	void SubmitCollisionTest(Collidable* col);
};

#endif _OctreeNode