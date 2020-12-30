// Bullet AOE Factory

#ifndef _BulletAOEFactory
#define _BulletAOEFactory

#include "AzulCore.h"
#include "BulletAOE.h"
#include "BulletAOEObjectPool.h"

#include <list>

class BulletAOEFactory
{
private:
	static BulletAOEFactory* ptrInstance;

	static BulletAOEFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new BulletAOEFactory();
		return *ptrInstance;
	}

	BulletAOEFactory();
	BulletAOEFactory(const BulletAOEFactory& other) = delete;
	BulletAOEFactory& operator=(const BulletAOEFactory& other) = delete;
	~BulletAOEFactory() = default;

	void privCreateExplosion(Vect pos);

	BulletAOEObjectPool explosionObjPool;
	std::list<BulletAOE*> explosionList;

public:
	static void CreateExplosion(Vect pos) { Instance().privCreateExplosion(pos); };
	static void ExplosionReturn(BulletAOE* b);

	static void Delete();
};

#endif _BulletFactory