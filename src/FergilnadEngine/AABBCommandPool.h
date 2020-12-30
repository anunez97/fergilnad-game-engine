// AABB Command Pool

#ifndef _AABBCommandPool
#define _AABBCommanddPool

#include <stack>

class VisualizeAABBCommand;

class AABBCommandPool
{
public:
	AABBCommandPool();
	AABBCommandPool(const AABBCommandPool& other) = delete;
	AABBCommandPool& operator=(const AABBCommandPool& other) = delete;
	~AABBCommandPool();

	VisualizeAABBCommand* GetCommand();
	void ReturnCommand(VisualizeAABBCommand* cmd);

private:
	std::stack<VisualizeAABBCommand*> recycledCmds;
};

#endif _AABBCommandPool