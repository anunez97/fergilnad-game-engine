// Player

#ifndef _PlayerTank
#define _PlayerTank

#include "GameObject.h"

class EnemyBullet;
class Terrain;

class PlayerTank : public GameObject
{
public:
	PlayerTank();
	PlayerTank(const PlayerTank& other) = delete;
	PlayerTank& operator=(const PlayerTank& other) = delete;
	~PlayerTank();

	virtual void Update();
	virtual void Draw();

	virtual void Collision(Collidable*) {};
	virtual void Collision(EnemyBullet* );
	virtual void CollisionTerrain();

	virtual void SceneEntry();
	virtual void SceneExit();

	void Initialize();

	void MoveForward();
	void MoveBackward();
	void TurnLeft();
	void TurnRight();

	void LookUp();
	void LookDown();
	void LookLeft();
	void LookRight();

	void Fire();
	void Reload();

	int GetReloadTime();

	Vect GetPos();

private:
	GraphicsObject_TextureLight* pBody;
	GraphicsObject_TextureLight* pTurret;

	Matrix WorldMat;
	Matrix ScaleMat;
	Matrix BodyRotateMat;
	Matrix TurretRotateMat;
	Matrix CamMatrix;
	
	Vect Pos;
	Vect TurretBarrel;
	Vect TurretBarrelEnd;

	const float speed;
	const float rotAngle;
	const float turretOffset;
	const float turretEndBarrel;
	const int maxReloadTime;

	float tilt;
	float tiltangle;

	int reloadtime;
	int health;

	bool reloaded;

};

#endif _PlayerTank