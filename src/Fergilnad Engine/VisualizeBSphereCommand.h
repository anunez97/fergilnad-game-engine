// Visualize BSphere Command

#ifndef _VisualizeBSphereCommand
#define _VisualizeBSphereCommand

#include "VisualizeCommandBase.h"

class VisualizeBSphereCommand : public VisualizeCommandBase
{
public:
	VisualizeBSphereCommand() = default;
	VisualizeBSphereCommand(const VisualizeBSphereCommand& other) = delete;
	VisualizeBSphereCommand& operator=(const VisualizeBSphereCommand& other) = delete;
	~VisualizeBSphereCommand() {};

	VisualizeBSphereCommand(Matrix& m, const Vect& color);

	void Execute();
	void Return();

	void SetWorldColor(Matrix m, Vect col);


private:
	Matrix World;
	Vect Color;

};

#endif _VisualizeBSphereCommand