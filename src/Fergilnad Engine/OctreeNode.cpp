// Octree Node

#include "OctreeNode.h"
#include "FGNMathTools.h"
#include "VisualizerAttorney.h"
#include "CollidableAttorney.h"
#include "TrimBranchCommand.h"
#include "SceneAttorney.h"

OctreeNode::OctreeNode(Vect _min, Vect _max, OctreeNode* parent)
	:MIN_LENGTH(1.0f), pParent(parent), DeleteTimerReset(5), DeleteTimer(-1), NODE_INDEX(0), TREE_BUILT(false), TREE_READY(false)
{
	pTrimCommand = new TrimBranchCommand(this);
	ChildrenList = new OctreeNode * [MAX_CHILD_COUNT];

	boundingArea.set(_min, _max);

	Vect center = _min + ((_max - _min) * .5f);

	for (int i = 0; i < MAX_CHILD_COUNT; i++)
	{
		ChildrenList[i] = 0;
	}

	// gets the bounding area for potential child nodes
	CalculateChildAreas();
}

OctreeNode::OctreeNode(BoundingArea area, OctreeNode* parent, int index)
	:MIN_LENGTH(1.0f), pParent(parent), DeleteTimerReset(5), DeleteTimer(-1), NODE_INDEX(0), TREE_BUILT(false), TREE_READY(false)
{
	NODE_INDEX = index;

	pTrimCommand = new TrimBranchCommand(this);

	boundingArea = area;

	ChildrenList = new OctreeNode * [MAX_CHILD_COUNT];

	Vect center = area.min + ((area.max - area.min) * .5f);

	for (int i = 0; i < MAX_CHILD_COUNT; i++)
	{
		ChildrenList[i] = 0;
	}

	// gets the bounding area for potential child nodes
	CalculateChildAreas();
}

OctreeNode::~OctreeNode()
{
	for (int i = 0; i < MAX_CHILD_COUNT; i++)
	{
		delete ChildrenList[i];
	}

	delete[] ChildrenList;

	delete pTrimCommand;
}

OctreeNode* OctreeNode::CreateNode(BoundingArea area, int index)
{
	// if there's a child node at this index just return the pointer to it
	if (ChildrenList[index] != 0)
		return ChildrenList[index];

	// if the current octant is the smallest size
	if (boundingArea.max.X() - boundingArea.min.X() <= MIN_LENGTH)
		return 0;

	// creates the new node
	OctreeNode* node = new OctreeNode(area, this, index);


	node->pParent = this;

	node->NODE_INDEX = index;

	// gives the node the collision tests that the parent has
	node->colTestList = this->colTestList;

	return node;
}

void OctreeNode::Update()
{
	// Update the tree first
	UpdateTree();

	if (TREE_BUILT && TREE_READY)
	{
		// empty node
		if (objectList.size() == 0)
		{
			// has no children
			if (!CheckForChildren())
			{
				// start the deletion timer
				if (DeleteTimer == -1)
					DeleteTimer = DeleteTimerReset;

				// countdown the timer
				else if (DeleteTimer > 0)
				{
					DeleteTimer--;
					return;
				}
				// submit this node to be trimmed
				else
				{
					SubmitTrim();
					DeleteTimer = -1;
					return;
				}
			}
		}
		// not an empty node
		else
		{
			// if the node has no children it is a leaf node
			if (!CheckForChildren())
				TREE_BUILT = false;

			// Turn off the deletion timer if it was active
			if (DeleteTimer != -1)
				DeleteTimer = -1;
		}

		ObjectList movedObjList;

		for (ObjectList::iterator it = objectList.begin(); it != objectList.end(); it++)
		{
			// check if the object does not fit in this node's bounding area
			if (!FitsInArea(*it, boundingArea))
			{
				// if this node has no parent, the tree will have to be rebuilt
				if (pParent == 0)
				{
					DebugMsg::out("object is out of bounds\n");
					SceneAttorney::Registration::GetCollisionManager()->RebuildTree();
					return;
				}

				movedObjList.push_back(*it);

				// the tree is no longer ready since it has changed
				TREE_READY = false;
			}
		}

		for (ObjectList::iterator it = movedObjList.begin(); it != movedObjList.end(); it++)
		{
			OctreeNode* curr = this;

			while (curr->pParent != 0)
			{
				// find a node that the object will fit in
				if (curr->FitsInArea(*it, curr->boundingArea))
				{
					break;
				}
				else
				{
					// if the current node has no parent then the tree will have to be rebuilt
					if (curr->pParent == 0)
					{
						DebugMsg::out("object is out of bounds\n");
						SceneAttorney::Registration::GetCollisionManager()->RebuildTree();
						return;
					}
					curr = curr->pParent;
				}
			}

			objectList.remove(*it);
			curr->Insert(*it);
		}

		// update any child nodes
		for (int i = 0; i < MAX_CHILD_COUNT; i++)
		{
			if (ChildrenList[i] != 0)
			{
				ChildrenList[i]->Update();
			}
		}
	}
	// this applies to leaf nodes only
	else
	{
		ObjectList movedObjList;

		// get any objects that no longer fit in this node
		for (ObjectList::iterator it = objectList.begin(); it != objectList.end(); it++)
		{
			if (!FitsInArea(*it, boundingArea))
			{
				movedObjList.push_back(*it);
				TREE_READY = false;
			}
		}

		// find a node the object will fit in and send it there
		for (ObjectList::iterator it = movedObjList.begin(); it != movedObjList.end(); it++)
		{
			OctreeNode* curr = this;

			// go up the tree and find a node that will fit the object
			while (curr->pParent != 0)
			{
				if (curr->FitsInArea(*it, curr->boundingArea))
				{
					break;
				}
				else
				{
					// if there is no parent node, the tree needs to be rebuilt
					if (curr->pParent == 0)
					{
						DebugMsg::out("object is out of bounds\n");
						SceneAttorney::Registration::GetCollisionManager()->RebuildTree();
						return;
					}
					curr = curr->pParent;
				}
			}

			// there is no parent node to check so the tree will need to be rebuilt
			if (pParent == 0)
			{
				DebugMsg::out("object is out of bounds\n");
				SceneAttorney::Registration::GetCollisionManager()->RebuildTree();
				return;
			}

			objectList.remove(*it);
			curr->Insert(*it);
		}

		// attempt another update if there are objects to be inserted/removeed
		if (objInsertQueue.size() > 0 || objRemoveQueue.size() > 0)
		{
			Update();
		}

		// no objects in the node
		if (objectList.size() == 0)
		{
			// start the deletion timer
			if (DeleteTimer == -1)
			{
				DeleteTimer = DeleteTimerReset;
			}
			// countdown the timer
			else if (DeleteTimer > 0)
			{
				DeleteTimer--;
				return;
			}
			// submit this node to be trimmed
			else
			{
				SubmitTrim();
				DeleteTimer = -1;
				return;
			}
		}
		else
		{
			// Turn off the deletion timer if it was active
			if (DeleteTimer != -1)
				DeleteTimer = -1;
		}
		
	}
}

void OctreeNode::UpdateTree()
{
	if (!TREE_BUILT)
	{
		// remove any pending objects
		while (objRemoveQueue.size() > 0)
		{
			objectList.remove(objRemoveQueue.front());
			objRemoveQueue.pop();
		}

		// insert any pending objects
		while (objInsertQueue.size() > 0)
		{
			objectList.push_back(objInsertQueue.front());
			CollidableAttorney::Octree::SetParentNode(objInsertQueue.front(), this);
			objInsertQueue.pop();
		}

		// Build the tree
		BuildTree();

		TREE_BUILT = true;
	}
	else
	{
		// remove any pending objects
		while (objRemoveQueue.size() > 0)
		{
			objectList.remove(objRemoveQueue.front());
			objRemoveQueue.pop();
		}

		// insert any pending objects
		while (objInsertQueue.size() > 0)
		{
			Insert(objInsertQueue.front());
			objInsertQueue.pop();
		}
	}

	TREE_READY = true;
}

void OctreeNode::BuildTree()
{
	// The node only has a a single object or none; no reason to attempt to build a tree
	if (objectList.size() <= 1)
		return;

	ObjectList movedObjList;

	for (ObjectList::iterator it = objectList.begin(); it != objectList.end(); it++)
	{
		for (int i = 0; i < MAX_CHILD_COUNT; i++)
		{
			// check if any objects can fit in a child node
			if (FitsInArea(*it, ChildrenBoundingAreas[i]))
			{
				// Create the child node if it doesn't exist
				ChildrenList[i] = CreateNode(ChildrenBoundingAreas[i], i);

				// triggers when this node is the smallest size 
				if (ChildrenList[i] == 0)
					break;

				// insert the object into the child's queue
				ChildrenList[i]->InsertObjQueue(*it);

				// update the child node's tree
				ChildrenList[i]->UpdateTree();

				// object no longer belongs to this node
				movedObjList.push_back(*it);
				break;
			}
		}
	}

	// removed any moved objects from this node
	for (ObjectList::iterator it = movedObjList.begin(); it != movedObjList.end(); it++)
	{
		objectList.remove(*it);
	}
	movedObjList.clear();

	// tree is now built
	TREE_BUILT = true;
}

void OctreeNode::Insert(Collidable* col)
{
	// If the node has no objects, just insert the object 
	if (objectList.size() == 0)
	{
		objectList.push_back(col);
		CollidableAttorney::Octree::SetParentNode(col, this);
		return;
	}

	// if the octant is the smallest size, insert it and leave
	if (boundingArea.max.X() - boundingArea.min.X() == MIN_LENGTH)
	{
		objectList.push_back(col);
		CollidableAttorney::Octree::SetParentNode(col, this);
		return;
	}

	// if the object does not fit in this node, send it to the parent node
	if (!FitsInArea(col, boundingArea))
	{
		if (pParent != 0)
		{
			pParent->Insert(col);
			return;
		}
		else
		{
			// the object does not fit in the root so the tree needs to be rebuilt
			DebugMsg::out("object out of bounds...\n");
			SceneAttorney::Registration::GetCollisionManager()->RebuildTree();
			return;
		}
	}

	// look through child nodes
	for (int i = 0; i < MAX_CHILD_COUNT; i++)
	{
		// if the object fits in a child node insert it there
		if (FitsInArea(col, ChildrenBoundingAreas[i]))
		{
			// Create a child node, if it doesnt exist
			ChildrenList[i] = CreateNode(ChildrenBoundingAreas[i], i);

			// Insert the object into the child node
			ChildrenList[i]->Insert(col);

			return;
		}
	}

	// If the object does not fit in the child node insert it in this node
	objectList.push_back(col);
	CollidableAttorney::Octree::SetParentNode(col, this);
}

void OctreeNode::InsertObjQueue(Collidable* col)
{
	// object is inserted in the node's pending queue
	objInsertQueue.push(col);
}

void OctreeNode::RemoveObject(Collidable* col)
{
	// object is now pending to be removed
	objRemoveQueue.push(col);
}

void OctreeNode::SubmitTrim()
{
	// check if node is not the root
	if (pParent != 0)
		pParent->trimCmdList.push_back(pTrimCommand);

}

void OctreeNode::TrimBranches()
{
	// Process any trim commands
	for (std::list<TrimBranchCommand*>::iterator it = trimCmdList.begin(); it != trimCmdList.end(); it++)
	{
		// Get the node's index
		int index = (*it)->GetNode()->NODE_INDEX;

		// Delete the node
		(*it)->Execute();

		// Fix pointers
		ChildrenList[index] = 0;
	}

	trimCmdList.clear();

	// For any branches that remain, process their commands
	for (int i = 0; i < MAX_CHILD_COUNT; i++)
	{
		if (ChildrenList[i] != 0)
			ChildrenList[i]->TrimBranches();
	}
}

void OctreeNode::Render()
{
	RenderNode();

	for (int i = 0; i < MAX_CHILD_COUNT; i++)
	{
		if (ChildrenList[i] != 0)
		{
			ChildrenList[i]->Render();
		}
	}
}

void OctreeNode::RenderNode()
{
	// Renders a red cube if the octant has objects in it, blue if not
	if (objectList.size() > 0)
	{
		VisualizerAttorney::Show::AABB(boundingArea.min, boundingArea.max, Color::Red);
	}
	else
		VisualizerAttorney::Show::AABB(boundingArea.min, boundingArea.max, Color::Blue);
}

bool OctreeNode::FitsInArea(Collidable* col, BoundingArea area)
{
	Vect c = CollidableAttorney::Volume::GetCollisionBSphere(col).GetCenter();
	float radius = CollidableAttorney::Volume::GetCollisionBSphere(col).GetRadius();

	Vect colmin = c - Vect(radius, radius, radius);
	Vect colmax = c + Vect(radius, radius, radius);

	// test if an AABB based off the object's default BSphere is completely within a node's bounding area

	if (FGNMathTools::PointInAABB(colmin, area.min, area.max))
	{
		if (FGNMathTools::PointInAABB(colmax, area.min, area.max))
		{
			return true;
		}
	}

	return false;
}

bool OctreeNode::CheckForChildren()
{
	for (int i = 0; i < MAX_CHILD_COUNT; i++)
	{
		if (ChildrenList[i] != 0)
			return true;
	}

	return false;
}

void OctreeNode::CalculateChildAreas()
{
	Vect center = boundingArea.min + ((boundingArea.max - boundingArea.min) * .5f);

	// Bottom - NorthWest/East
	ChildrenBoundingAreas[0].set(Vect(boundingArea.min.X(), boundingArea.min.Y(), center.Z()), Vect(center.X(), center.Y(), boundingArea.max.Z()));
	ChildrenBoundingAreas[1].set(Vect(center.X(), boundingArea.min.Y(), center.Z()), Vect(boundingArea.max.X(), center.Y(), boundingArea.max.Z()));

	// Bottom - SouthWest/East
	ChildrenBoundingAreas[2].set(boundingArea.min, center);
	ChildrenBoundingAreas[3].set(Vect(center.X(), boundingArea.min.Y(), boundingArea.min.Z()), Vect(boundingArea.max.X(), center.Y(), center.Z()));

	// Top - NorthWest/East
	ChildrenBoundingAreas[4].set(Vect(boundingArea.min.X(), center.Y(), center.Z()), Vect(center.X(), boundingArea.max.Y(), boundingArea.max.Z())); // Top - NorthWest
	ChildrenBoundingAreas[5].set(center, boundingArea.max); // Top - NorthEast

	// Top - SouthWest/East
	ChildrenBoundingAreas[6].set(Vect(boundingArea.min.X(), center.Y(), boundingArea.min.Z()), Vect(center.X(), boundingArea.max.Y(), center.Z()));
	ChildrenBoundingAreas[7].set(Vect(center.X(), center.Y(), boundingArea.min.Z()), Vect(boundingArea.max.X(), boundingArea.max.Y(), center.Z()));
}

void OctreeNode::ProcessCollisions()
{
	// check for collisions 
	for (CollisionTestList::iterator it = colTestList.begin(); it != colTestList.end(); it++)
	{
		(*it)->SetNode(this);
		(*it)->Execute();
	}

	//* go through the node's objects
	for (ObjectList::iterator it = objectList.begin(); it != objectList.end(); it++)
	{
		for (int i = 0; i < MAX_CHILD_COUNT; i++)
		{
			if (ChildrenList[i] != 0)
			{
				// check the object's BSphere against the child node AABB
				if (FGNMathTools::Intersect(ChildrenBoundingAreas[i].min, ChildrenBoundingAreas[i].max, CollidableAttorney::Volume::GetCollisionBSphere(*it)))
				{
					// sends the object to be tested by the child node
					ChildrenList[i]->SubmitCollisionTest(*it);
				}
			}
		}
	}
	//*/

	//* do the same test except for the objects sent by the parent nodes
	for (ObjectList::iterator it = parentObjectList.begin(); it != parentObjectList.end(); it++)
	{
		// loop through the node's children
		for (int i = 0; i < MAX_CHILD_COUNT; i++)
		{
			// if the child node exists
			if (ChildrenList[i] != 0)
			{
				// check the object's BSphere against the child node AABB
				if (FGNMathTools::Intersect(ChildrenBoundingAreas[i].min, ChildrenBoundingAreas[i].max, CollidableAttorney::Volume::GetCollisionBSphere(*it)))
				{
					// sends the object to be tested by the child node
					ChildrenList[i]->SubmitCollisionTest(*it);
				}
			}
		}
	}
	//*/

	// clear the list given by the parent nodes
	parentObjectList.clear();

	// have the child nodes process their collisions
	for (int i = 0; i < MAX_CHILD_COUNT; i++)
	{
		if (ChildrenList[i] != 0)
			ChildrenList[i]->ProcessCollisions();
	}
}

void OctreeNode::SubmitCollisionTest(Collidable* col)
{
	// objects sent by the parent node to be tested
	parentObjectList.push_back(col);
}

void OctreeNode::AddCollisionTest(OctreeTestCommandBase* command)
{
	colTestList.push_back(command);

	if (CheckForChildren())
	{
		// send the command to all child nodes
		for (int i = 0; i < MAX_CHILD_COUNT; i++)
		{
			if (ChildrenList[i] != 0)
				ChildrenList[i]->AddCollisionTest(command);
		}
	}
}