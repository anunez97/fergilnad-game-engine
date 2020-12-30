// BSphere Command Factory

#ifndef _BSphereCommandFactory
#define _BSphereCommandFactory

#include "VisualizeBSphereCommand.h"
#include "BSphereCmdPool.h"

#include <list>

class VisualizeBSphereCommand;

class BSphereCommandFactory
{
private:
	static BSphereCommandFactory* ptrInstance;

	static BSphereCommandFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new BSphereCommandFactory;
		return *ptrInstance;
	}

	BSphereCommandFactory();
	BSphereCommandFactory(const BSphereCommandFactory& other) = delete;
	BSphereCommandFactory& operator=(const BSphereCommandFactory& other) = delete;
	~BSphereCommandFactory() = default;

	VisualizeBSphereCommand* privCreateCommand(Matrix& m, const Vect& col);

	BSphereCmdPool cmdPool;
	std::list<VisualizeBSphereCommand*> cmdList;

public:
	static VisualizeBSphereCommand* CreateCommand(Matrix& m, const Vect& col) { return Instance().privCreateCommand(m, col); };
	static void CommandReturn(VisualizeBSphereCommand* cmd);
	static void Delete();

};

#endif _BSphereCommandFactory