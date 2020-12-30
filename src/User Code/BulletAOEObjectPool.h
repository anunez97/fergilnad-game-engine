// Bullet AOE Object Pool

#ifndef _BulletAOEObjectPool
#define _BulletAOEObjectPool

#include <stack>

class BulletAOE;

class BulletAOEObjectPool
{
public:
	BulletAOEObjectPool();
	BulletAOEObjectPool(BulletAOEObjectPool& other) = delete;
	BulletAOEObjectPool& operator=(BulletAOEObjectPool& other) = delete;
	~BulletAOEObjectPool();

	BulletAOE* GetExplosion();

	void ReturnExplosion(BulletAOE* b);

private:
	std::stack<BulletAOE*> recycledExplosions;
};

#endif _BulletAOEObjectPool