// Bullet Factory

#ifndef _BulletFactory
#define _BulletFactory

#include "AzulCore.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"
#include "Bullet.h"
#include "BulletObjectPool.h"

#include <list>

class BulletFactory
{
private:
	static BulletFactory* ptrInstance;

	static BulletFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new BulletFactory();
		return *ptrInstance;
	}

	BulletFactory();
	BulletFactory(const BulletFactory& other) = delete;
	BulletFactory& operator=(const BulletFactory& other) = delete;
	~BulletFactory() = default;

	void privCreatePlayerBullet(Matrix rot, Vect pos);
	void privCreateEnemyBullet(Matrix rot, Vect pos);

	BulletObjectPool bulletObjPool;
	std::list<PlayerBullet*> playerBulletList;
	std::list<EnemyBullet*> enemyBulletList;
	
public:
	static void CreatePlayerBullet(Matrix rot, Vect pos) { Instance().privCreatePlayerBullet(rot, pos); };
	static void CreateEnemyBullet(Matrix rot, Vect pos) { Instance().privCreateEnemyBullet(rot, pos); }
	static void BulletReturn(PlayerBullet* b);
	static void BulletReturn(EnemyBullet* b);

	static void Delete();
};

#endif _BulletFactory