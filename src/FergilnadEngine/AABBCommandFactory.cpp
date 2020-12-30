// AABB Command Factory

#include "AABBCommandFactory.h"

AABBCommandFactory* AABBCommandFactory::ptrInstance = nullptr;

AABBCommandFactory::AABBCommandFactory()
{

}

VisualizeAABBCommand* AABBCommandFactory::privCreateCommand(Matrix &m, const Vect& col)
{
	VisualizeAABBCommand* aabb;

	aabb = cmdPool.GetCommand();

	aabb->SetWorldColor(m, col);

	cmdList.push_back(aabb);

	return aabb;
}

void AABBCommandFactory::CommandReturn(VisualizeAABBCommand* cmd)
{
	Instance().cmdList.remove(cmd);
	Instance().cmdPool.ReturnCommand(cmd);
}

void AABBCommandFactory::Delete()
{
	for (std::list<VisualizeAABBCommand*>::iterator it = Instance().cmdList.begin(); it != Instance().cmdList.end(); it++)
	{
		delete (*it);
	}

	delete ptrInstance;
	ptrInstance = nullptr;
}