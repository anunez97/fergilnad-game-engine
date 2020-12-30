// Visualize AABB Command

#include "VisualizeAABBCommand.h"
#include "VisualizerAttorney.h"
#include "AABBCommandFactory.h"

VisualizeAABBCommand::VisualizeAABBCommand(Matrix& m, const Vect& color)
{
	World = m;
	Color = color;
}

void VisualizeAABBCommand::Execute()
{
	VisualizerAttorney::Render::AABB(World, Color);
}

void VisualizeAABBCommand::Return()
{
	AABBCommandFactory::CommandReturn(this);
}

void VisualizeAABBCommand::SetWorldColor(Matrix m, Vect col)
{
	World = m;
	Color = col;
}