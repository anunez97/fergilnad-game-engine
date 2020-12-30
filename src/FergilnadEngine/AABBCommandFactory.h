// AABB Command Factory

#ifndef _AABBCommandFactory
#define _AABBCommandFactory

#include "VisualizeAABBCommand.h"
#include "AABBCommandPool.h"

#include <list>

class VisualizeBSphereCommand;

class AABBCommandFactory
{
private:
	static AABBCommandFactory* ptrInstance;

	static AABBCommandFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new AABBCommandFactory;
		return *ptrInstance;
	}

	AABBCommandFactory();
	AABBCommandFactory(const AABBCommandFactory& other) = delete;
	AABBCommandFactory& operator=(const AABBCommandFactory& other) = delete;
	~AABBCommandFactory() = default;

	VisualizeAABBCommand* privCreateCommand(Matrix& m, const Vect& col);

	AABBCommandPool cmdPool;
	std::list<VisualizeAABBCommand*> cmdList;

public:
	static VisualizeAABBCommand* CreateCommand(Matrix& m, const Vect& col) { return Instance().privCreateCommand(m, col); };
	static void CommandReturn(VisualizeAABBCommand* cmd);
	static void Delete();

};

#endif _AABBCommandFactory