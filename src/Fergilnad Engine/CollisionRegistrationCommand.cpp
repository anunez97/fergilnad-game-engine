// Collision Registration Command

#include "CollisionRegistrationCommand.h"
#include "CollidableAttorney.h"

CollisionRegistrationCommand::CollisionRegistrationCommand(Collidable* col)
	:pCollide(col)
{
}

void CollisionRegistrationCommand::Execute()
{
	CollidableAttorney::SceneRegistration::Register(pCollide);
	//pCollide->SceneRegistration();
}