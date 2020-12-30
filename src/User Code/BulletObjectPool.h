// Bullet Object Pool

#ifndef _BulletObjectPool
#define _BulletObjectPool

#include <stack>

class PlayerBullet;
class EnemyBullet;

class BulletObjectPool
{
public:
	BulletObjectPool();
	BulletObjectPool(BulletObjectPool& other) = delete;
	BulletObjectPool& operator=(BulletObjectPool& other) = delete;
	~BulletObjectPool();

	PlayerBullet* GetPlayerBullet();
	EnemyBullet* GetEnemyBullet();

	void ReturnBullet(PlayerBullet* b);
	void ReturnBullet(EnemyBullet* b);

private:
	std::stack<PlayerBullet*> recycledPBullets;
	std::stack<EnemyBullet*> recycledEBullets;
};

#endif _BulletObjectPool