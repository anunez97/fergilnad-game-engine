// Collision Deregistration Command

#include "CollisionDeregistrationCommand.h"
#include "CollidableAttorney.h"

CollisionDeregistrationCommand::CollisionDeregistrationCommand(Collidable* col)
	:pCollide(col)
{
}

void CollisionDeregistrationCommand::Execute()
{
	CollidableAttorney::SceneRegistration::Deregister(pCollide);
	//pCollide->SceneDeregistration();
}