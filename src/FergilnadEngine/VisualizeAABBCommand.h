// Visualize AABB Command

#ifndef _VisualizeAABBCommand
#define _VisualizeAABBCommand

#include "VisualizeCommandBase.h"

class VisualizeAABBCommand : public VisualizeCommandBase
{
public:
	VisualizeAABBCommand() = default;
	VisualizeAABBCommand(const VisualizeAABBCommand& other) = delete;
	VisualizeAABBCommand& operator=(const VisualizeAABBCommand& other) = delete;
	~VisualizeAABBCommand() {};

	VisualizeAABBCommand(Matrix& m, const Vect& color);

	void Execute();
	void Return();

	void SetWorldColor(Matrix m, Vect col);


private:
	Matrix World;
	Vect Color;

};

#endif _VisualizeAABBCommand