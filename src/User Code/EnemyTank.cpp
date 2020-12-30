// Enemy Tank

#include "EnemyTank.h"
#include "BulletFactory.h"
#include "PlayerTank.h"

#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "SceneManager.h"

#include "Visualizer.h"
#include "EnemyTankFactory.h"
#include "EnemyManager.h"

#include "BaseAI.h"

EnemyTank::EnemyTank()
	:speed(1.0f), rotAngle(0.05f), turretOffset(7.0f), turretEndBarrel(30.0f), turretRotSpeed(0.03f), bodyrotatespeed(0.8f)
{
}

EnemyTank::EnemyTank(Model* body, Model* turret, ShaderObject* shader, Texture* tex)
	:speed(0.75f), rotAngle(0.05f), turretOffset(7.0f), turretEndBarrel(30.0f), turretRotSpeed(0.03f), bodyrotatespeed(0.5f)
{
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);

	pBody = new GraphicsObject_TextureLight(body, shader, tex, LightColor, LightPos);
	pTurret = new GraphicsObject_TextureLight(turret, shader, tex, LightColor, LightPos);

	ScaleMat.set(SCALE, 0.5f, 0.5f, 0.5f);
	//ScaleMat.set(SCALE, 1.0f, 1.0f, 1.0f);
	BodyRotateMat.set(IDENTITY);
	TurretRotateMat.set(IDENTITY);

	// tank body
	Pos.set(0, 0, 0);
	BodyWorldMat = ScaleMat * BodyRotateMat * Matrix(TRANS, Pos);
	pBody->SetWorld(BodyWorldMat);

	// tank turret
	//TurretBarrelEnd.set(0, 2.0f, turretEndBarrel);
	TurretBarrelEnd.set(0, 1.5f, turretEndBarrel);
	TurretWorldMat = ScaleMat * TurretRotateMat * Matrix(TRANS, Pos + Vect(0, turretOffset, 0));
	pTurret->SetWorld(TurretWorldMat);

	SetColliderModel(pBody->getModel(), OBB);
	SetCollidableGroup<EnemyTank>();
}

EnemyTank::~EnemyTank()
{
	delete pBody;
	delete pTurret;
}

void EnemyTank::Initialize(const Vect pos, BaseAI* ai, EnemyTank::Type t)
{
	Pos = pos;
	pAI = ai;
	type = t;

	Matrix mtrans = Matrix(TRANS, Pos);
	BodyWorldMat = ScaleMat * BodyRotateMat * mtrans;
	TurretWorldMat = ScaleMat * TurretRotateMat * mtrans;

	pBody->SetWorld(BodyWorldMat);
	pTurret->SetWorld(TurretWorldMat);

	UpdateCollisionData(BodyWorldMat);
}

void EnemyTank::SceneEntry()
{
	SubmitUpdateRegistration();
	SubmitDrawRegistration();
	SubmitAlarmRegistration(ALARM_ID::ALARM_0, 3.0f);

	SubmitCollisionRegistration();
}

void EnemyTank::SceneExit()
{
	SubmitUpdateDeregistration();

	SubmitDrawDeregistration();

	SubmitAlarmDeregistration(ALARM_ID::ALARM_0);

	SubmitCollisionDeregistration();

	EnemyTankFactory::TankReturn(this);
}

void EnemyTank::Update()
{
	pAI->Execute(this);

	TurretBarrel = Pos + Vect(0, turretOffset, 0);

	UpdateCollisionData(BodyWorldMat);
}

void EnemyTank::Draw()
{
	pBody->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
	pTurret->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}

void EnemyTank::Alarm0()
{
	//BulletFactory::CreateEnemyBullet(TurretRotateMat, TurretBarrel + TurretBarrelEnd * TurretRotateMat);
	SubmitAlarmRestart(ALARM_ID::ALARM_0, 3.0f);
	//SubmitAlarmRegistration(ALARM_ID::ALARM_0, 3.0f);
}

void EnemyTank::Collision(PlayerBullet* )
{
	EnemyManager::EnemyKilled(this);

	SubmitExit();
}

void EnemyTank::SetPlayer(PlayerTank* tank)
{
	pPlayer = tank;
}

void EnemyTank::LookAt(Vect target)
{
	// Direction vector to player
	Vect dir = (target - Pos).norm();

	// Angle between the direction and forward
	float angle = (TurretWorldMat.get(ROW_0).dot(dir)) / (TurretWorldMat.get(ROW_0).mag() * dir.mag());

	// Rotate turret by angle 
	TurretRotateMat *= Matrix(ROT_Y, angle * turretRotSpeed);

	// Update world matrix
	TurretWorldMat = ScaleMat * TurretRotateMat * Matrix(TRANS, Pos + Vect(0, turretOffset, 0));

	pTurret->SetWorld(TurretWorldMat);
}

void EnemyTank::MoveTo(Vect target)
{
	// Direction vector to target
	Vect dir = (target - Pos).norm();

	// Current position and direction
	Pos += dir;

	// Angle between the direction and forward
	float angle = (BodyWorldMat.get(ROW_0).dot(dir)) / (BodyWorldMat.get(ROW_0).mag() * dir.mag());

	// Rotate by angle 
	BodyRotateMat *= Matrix(ROT_Y, angle * bodyrotatespeed);

	// Update world matrix
	BodyWorldMat = ScaleMat * BodyRotateMat * Matrix(TRANS, Pos);
	pBody->SetWorld(BodyWorldMat);

	TurretWorldMat = ScaleMat * TurretRotateMat * Matrix(TRANS, Pos + Vect(0, turretOffset, 0));
	pTurret->SetWorld(TurretWorldMat);
}

Vect EnemyTank::GetPos()
{
	return Pos;
}

PlayerTank* EnemyTank::GetPlayer()
{
	return pPlayer;
}

EnemyTank::Type EnemyTank::GetType()
{
	return type;
}