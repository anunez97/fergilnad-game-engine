// Bullet Explosion Object Pool

#include "BulletAOEObjectPool.h"

#include "BulletAOE.h"

BulletAOEObjectPool::BulletAOEObjectPool()
{

}

BulletAOEObjectPool::~BulletAOEObjectPool()
{
	while (!recycledExplosions.empty())
	{
		delete recycledExplosions.top();
		recycledExplosions.pop();
	}
}

BulletAOE* BulletAOEObjectPool::GetExplosion()
{
	BulletAOE* b;

	if (recycledExplosions.empty())
	{
		b = new BulletAOE();
	}
	else
	{
		b = recycledExplosions.top();
		recycledExplosions.pop();
	}

	return b;
}

void BulletAOEObjectPool::ReturnExplosion(BulletAOE* b)
{
	recycledExplosions.push(b);
}