// Bullet Factory

#include "BulletFactory.h"
#include "Bullet.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

BulletFactory* BulletFactory::ptrInstance = nullptr;

BulletFactory::BulletFactory()
{
}

void BulletFactory::privCreatePlayerBullet(Matrix rot, Vect pos)
{
	PlayerBullet* b;

	b = bulletObjPool.GetPlayerBullet();

	b->Initialize(rot, pos);
	b->SubmitEntry();

	playerBulletList.push_back(b);
}

void BulletFactory::privCreateEnemyBullet(Matrix rot, Vect pos)
{
	EnemyBullet* b;

	b = bulletObjPool.GetEnemyBullet();

	b->Initialize(rot, pos);
	b->SubmitEntry();

	enemyBulletList.push_back(b);
}

void BulletFactory::BulletReturn(PlayerBullet* b)
{
	Instance().playerBulletList.remove(b);
	Instance().bulletObjPool.ReturnBullet(b);
}

void BulletFactory::BulletReturn(EnemyBullet* b)
{
	Instance().enemyBulletList.remove(b);
	Instance().bulletObjPool.ReturnBullet(b);
}

void BulletFactory::Delete()
{
	for (std::list<PlayerBullet*>::iterator it = Instance().playerBulletList.begin(); it != Instance().playerBulletList.end(); it++)
	{
		delete (*it);
	}

	for (std::list<EnemyBullet*>::iterator it = Instance().enemyBulletList.begin(); it != Instance().enemyBulletList.end(); it++)
	{
		delete (*it);
	}

	delete ptrInstance;
	ptrInstance = nullptr;
}