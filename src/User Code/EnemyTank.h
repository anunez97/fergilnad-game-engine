// Enemy Tank

#ifndef _EnemyTank
#define _EnemyTank

#include "GameObject.h"

class PlayerBullet;
class PlayerTank;
class BaseAI;

class EnemyTank : public GameObject
{
public:
	EnemyTank();
	EnemyTank(const EnemyTank& other) = delete;
	EnemyTank& operator=(const EnemyTank& other) = delete;
	~EnemyTank();

	enum Type
	{
		CHASER = 100,
		LONGRANGER = 150,
		PATROLLER = 200
	};

	EnemyTank(Model* body, Model* turret, ShaderObject* shader, Texture* tex);

	virtual void SceneEntry();
	virtual void SceneExit();

	virtual void Update();
	virtual void Draw();

	void Alarm0();

	virtual void Collision(Collidable*) {};
	virtual void Collision(PlayerBullet* );

	void Initialize(const Vect pos, BaseAI* ai, Type t);

	void SetPlayer(PlayerTank* tank);

	void LookAt(Vect pos);
	void MoveTo(Vect pos);

	Vect GetPos();
	PlayerTank* GetPlayer();
	Type GetType();

private:
	GraphicsObject_TextureLight* pBody;
	GraphicsObject_TextureLight* pTurret;

	BaseAI* pAI;

	PlayerTank* pPlayer;

	Matrix BodyWorldMat;
	Matrix TurretWorldMat;
	Matrix ScaleMat;
	Matrix BodyRotateMat;
	Matrix TurretRotateMat;

	Vect Pos;
	Vect TurretBarrel;
	Vect TurretBarrelEnd;

	const float speed;
	const float rotAngle;
	const float turretOffset;
	const float turretEndBarrel;
	const float turretRotSpeed;
	const float bodyrotatespeed;

	Type type;
};

#endif _EnemyTank