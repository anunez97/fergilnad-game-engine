// Collision Deregistration Command

#ifndef _CollisionDeregistrationCommand
#define _CollisionDeregistrationCommand

#include "SceneRegistrationCommand.h"

class Collidable;

class CollisionDeregistrationCommand : public SceneRegistrationCommand
{
public:
	CollisionDeregistrationCommand() {};
	CollisionDeregistrationCommand(const CollisionDeregistrationCommand& other) = delete;
	CollisionDeregistrationCommand& operator=(const CollisionDeregistrationCommand& other) = delete;
	~CollisionDeregistrationCommand() = default;

	CollisionDeregistrationCommand(Collidable* col);

	virtual void Execute();

private:
	Collidable* pCollide;

};

#endif _CollisionDeregistrationCommand