// Player Bullet

#ifndef _PlayerBullet
#define _PlayerBullet

#include "GameObject.h"

class EnemyTank;

class PlayerBullet : public GameObject
{
public:
	PlayerBullet();
	PlayerBullet(const PlayerBullet& other) = delete;
	PlayerBullet& operator=(const PlayerBullet& other) = delete;
	~PlayerBullet();

	virtual void SceneEntry();
	virtual void SceneExit();

	virtual void Update();
	virtual void Draw();

	void Alarm0();

	virtual void Collision(Collidable*) {};
	void Collision(EnemyTank*);

	void Initialize(Matrix rot, Vect pos);

private:
	GraphicsObject_TextureFlat* GO_Bullet;

	Vect Pos;

	Matrix WorldMat;
	Matrix ScaleMat;
	Matrix RotateMat;

	const float BulletSpeed;
};

#endif _PlayerBullet