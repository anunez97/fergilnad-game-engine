// Collision Dispatch Base

#ifndef _CollisionDispatchBase
#define _CollisionDispatchBase

class Collidable;

class CollisionDispatchBase
{
public:
	CollisionDispatchBase() {};
	CollisionDispatchBase(const CollisionDispatchBase& other) = delete;
	CollisionDispatchBase& operator=(const CollisionDispatchBase& other) = delete;
	virtual ~CollisionDispatchBase() {};

	virtual void ProcessCallbacks(Collidable* c1, Collidable* c2) { c1; c2; };
};

#endif _CollisionDispatchBase