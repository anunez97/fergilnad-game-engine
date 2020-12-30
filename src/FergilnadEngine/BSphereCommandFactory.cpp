// BSphere Command Factory

#include "BSphereCommandFactory.h"

BSphereCommandFactory* BSphereCommandFactory::ptrInstance = nullptr;

BSphereCommandFactory::BSphereCommandFactory()
{
}

VisualizeBSphereCommand* BSphereCommandFactory::privCreateCommand(Matrix& m, const Vect& col)
{
	VisualizeBSphereCommand* bs;

	bs = cmdPool.GetCommand();

	bs->SetWorldColor(m, col);

	cmdList.push_back(bs);

	return bs;
}

void BSphereCommandFactory::CommandReturn(VisualizeBSphereCommand* cmd)
{
	Instance().cmdList.remove(cmd);
	Instance().cmdPool.ReturnCommand(cmd);
}

void BSphereCommandFactory::Delete()
{
	for (std::list<VisualizeBSphereCommand*>::iterator it = Instance().cmdList.begin(); it != Instance().cmdList.end(); it++)
	{
		delete (*it);
	}

	delete ptrInstance;
	ptrInstance = nullptr;
}