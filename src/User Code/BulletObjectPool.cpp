// Bullet Object Pool

#include "BulletObjectPool.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"

BulletObjectPool::BulletObjectPool()
{

}

BulletObjectPool::~BulletObjectPool()
{
	while (!recycledPBullets.empty())
	{
		delete recycledPBullets.top();
		recycledPBullets.pop();
	}

	while (!recycledEBullets.empty())
	{
		delete recycledEBullets.top();
		recycledEBullets.pop();
	}
}

PlayerBullet* BulletObjectPool::GetPlayerBullet()
{
	PlayerBullet* b;

	if (recycledPBullets.empty())
	{
		b = new PlayerBullet();
		//DebugMsg::out("Created new bullet\n");
	}
	else
	{
		b = recycledPBullets.top();
		recycledPBullets.pop();
		//DebugMsg::out("Recycled bullet\n");
	}

	return b;
}

EnemyBullet* BulletObjectPool::GetEnemyBullet()
{
	EnemyBullet* b;

	if (recycledEBullets.empty())
	{
		b = new EnemyBullet();
		//DebugMsg::out("Created new bullet\n");
	}
	else
	{
		b = recycledEBullets.top();
		recycledEBullets.pop();
		//DebugMsg::out("Recycled bullet\n");
	}

	return b;
}

void BulletObjectPool::ReturnBullet(PlayerBullet* b)
{
	recycledPBullets.push(b);
}

void BulletObjectPool::ReturnBullet(EnemyBullet* b)
{
	recycledEBullets.push(b);
}