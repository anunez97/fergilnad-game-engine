// Bullet AOE

#ifndef _BulletAOE
#define _BulletAOE

#include "GameObject.h"

class PlayerTank;
class EnemyTank;

class BulletAOE : public GameObject
{
public:
	BulletAOE();
	BulletAOE(const BulletAOE& other) = delete;
	BulletAOE& operator=(const BulletAOE& other) = delete;
	~BulletAOE();

	// GameObject methods
	void Draw();
	void Update();

	void Collision(Collidable*) {};
	void Collision(PlayerTank* player);
	void Collision(EnemyTank* enemy);

	void SceneEntry();
	void SceneExit();

	// User methods
	void Initialize(Vect pos);

private:
	Matrix WorldMat;
	Vect Pos;
	GraphicsObject_TextureFlat* GO_Explosion;
	const float maxRadius;
	const float defaultRadius;
	const float radiusChange;
	float radius;
};

#endif _BulletAOE