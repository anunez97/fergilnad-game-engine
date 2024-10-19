// Collision Registration Command

#ifndef _CollisionRegistrationCommand
#define _CollisionRegsitrationCommand

#include "SceneRegistrationCommand.h"

class Collidable;

class CollisionRegistrationCommand : public SceneRegistrationCommand
{
public:
	CollisionRegistrationCommand() {};
	CollisionRegistrationCommand(const CollisionRegistrationCommand& other) = delete;
	CollisionRegistrationCommand& operator=(const CollisionRegistrationCommand& other) = delete;
	~CollisionRegistrationCommand() = default;

	CollisionRegistrationCommand(Collidable* col);

	virtual void Execute();

private:
	Collidable* pCollide;

};

#endif _CollisionRegistrationCommand