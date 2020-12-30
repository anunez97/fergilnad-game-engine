// Enemy Bullet

#ifndef _EnemyBullet
#define _EnemyBullet

#include "GameObject.h"

class PlayerTank;

class EnemyBullet : public GameObject
{
public:
	EnemyBullet();
	EnemyBullet(const EnemyBullet& other) = delete;
	EnemyBullet& operator=(const EnemyBullet& other) = delete;
	~EnemyBullet();

	virtual void SceneEntry();
	virtual void SceneExit();

	virtual void Update();
	virtual void Draw();

	void Alarm0();

	virtual void Collision(Collidable*) {};
	virtual void Collision(PlayerTank*);

	void Initialize(Matrix rot, Vect pos);

private:
	GraphicsObject_TextureFlat* GO_Bullet;

	Vect Pos;

	Matrix WorldMat;
	Matrix ScaleMat;
	Matrix RotateMat;

	const float BulletSpeed;
};

#endif _EnemyBullet