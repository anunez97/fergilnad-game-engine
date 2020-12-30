// BulletAOEFactory

#include "BulletAOEFactory.h"

#include "BulletAOE.h"

BulletAOEFactory* BulletAOEFactory::ptrInstance = nullptr;

BulletAOEFactory::BulletAOEFactory()
{
}

void BulletAOEFactory::privCreateExplosion(Vect pos)
{
	BulletAOE* b;

	b = explosionObjPool.GetExplosion();

	b->Initialize(pos);
	b->SubmitEntry();

	explosionList.push_back(b);
}

void BulletAOEFactory::ExplosionReturn(BulletAOE* b)
{
	Instance().explosionList.remove(b);
	Instance().explosionObjPool.ReturnExplosion(b);
}

void BulletAOEFactory::Delete()
{
	for (std::list<BulletAOE*>::iterator it = Instance().explosionList.begin(); it != Instance().explosionList.end(); it++)
	{
		delete (*it);
	}

	delete ptrInstance;
	ptrInstance = nullptr;
}