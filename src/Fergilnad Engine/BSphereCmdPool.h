// BSphere Command Pool

#ifndef _BSphereCmdPool
#define _BSphereCmdPool

#include <stack>

class VisualizeBSphereCommand;

class BSphereCmdPool
{
public:
	BSphereCmdPool();
	BSphereCmdPool(const BSphereCmdPool& other) = delete;
	BSphereCmdPool& operator=(const BSphereCmdPool& other) = delete;
	~BSphereCmdPool();

	VisualizeBSphereCommand* GetCommand();
	void ReturnCommand(VisualizeBSphereCommand* cmd);

private:
	std::stack<VisualizeBSphereCommand*> recycledCmds;

};

#endif _BSphereCmdPool