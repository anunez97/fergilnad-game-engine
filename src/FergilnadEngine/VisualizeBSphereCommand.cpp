// Visualize BSphere Command

#include "VisualizeBSphereCommand.h"
#include "VisualizerAttorney.h"
#include "BSphereCommandFactory.h"

VisualizeBSphereCommand::VisualizeBSphereCommand(Matrix& m, const Vect& color)
{
	World = m;
	Color = color;
}

void VisualizeBSphereCommand::Execute()
{
	VisualizerAttorney::Render::BSphere(World, Color);
}

void VisualizeBSphereCommand::Return()
{
	BSphereCommandFactory::CommandReturn(this);
}

void VisualizeBSphereCommand::SetWorldColor(Matrix m, Vect col)
{
	World = m;
	Color = col;
}