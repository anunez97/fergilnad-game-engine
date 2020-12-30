// AABB Command Pool

#include "AABBCommandPool.h"
#include "VisualizeAABBCommand.h"

AABBCommandPool::AABBCommandPool()
{

}

AABBCommandPool::~AABBCommandPool()
{
	while (!recycledCmds.empty())
	{
		delete recycledCmds.top();
		recycledCmds.pop();
	}
}

VisualizeAABBCommand* AABBCommandPool::GetCommand()
{
	VisualizeAABBCommand* aabb;

	if (recycledCmds.empty())
	{
		aabb = new VisualizeAABBCommand();
	}
	else
	{
		aabb = recycledCmds.top();
		recycledCmds.pop();
	}

	return aabb;
}

void AABBCommandPool::ReturnCommand(VisualizeAABBCommand* cmd)
{
	recycledCmds.push(cmd);
}