// BSphere Command Pool

#include "BSphereCmdPool.h"
#include "VisualizeBSphereCommand.h"

BSphereCmdPool::BSphereCmdPool()
{

}

BSphereCmdPool::~BSphereCmdPool()
{
	while (!recycledCmds.empty())
	{
		delete recycledCmds.top();
		recycledCmds.pop();
	}
}

VisualizeBSphereCommand* BSphereCmdPool::GetCommand()
{
	VisualizeBSphereCommand* bs;

	if (recycledCmds.empty())
	{
		bs = new VisualizeBSphereCommand();
	}
	else
	{
		bs = recycledCmds.top();
		recycledCmds.pop();
	}

	return bs;
}

void BSphereCmdPool::ReturnCommand(VisualizeBSphereCommand* cmd)
{
	recycledCmds.push(cmd);
}