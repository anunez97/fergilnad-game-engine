// Player Tank

#include "PlayerTank.h"

#include "PlayerManager.h"
#include "BulletFactory.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TerrainManager.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "ScreenLog.h"
#include "Terrain.h"
#include "Visualizer.h"

PlayerTank::PlayerTank()
	:speed(1.0f), rotAngle(0.025f), turretOffset(7.0f), turretEndBarrel(30.0f), reloaded(true), maxReloadTime(10), reloadtime(0), tilt(0.0f), tiltangle(0.2f), health(10)
{
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);

	pBody = new GraphicsObject_TextureLight(ModelManager::Get("tankbody"), ShaderManager::Get("TextureLight"), TextureManager::Get("blue"), TextureManager::Get("blue"), TextureManager::Get("blue"), LightColor, LightPos);
	pTurret = new GraphicsObject_TextureLight(ModelManager::Get("tankturret"), ShaderManager::Get("TextureLight"), TextureManager::Get("blue"), TextureManager::Get("blue"), TextureManager::Get("blue"), LightColor, LightPos);

	ScaleMat.set(SCALE, 0.5f, 0.5f, 0.5f);
	//ScaleMat.set(SCALE, 1.0f, 1.0f, 1.0f);
	BodyRotateMat.set(ROT_Y, 20.0f);
	TurretRotateMat.set(IDENTITY);

	// tank body
	Pos.set(0, 1000, 20);
	WorldMat = ScaleMat * BodyRotateMat * Matrix(TRANS, Pos);
	pBody->SetWorld(WorldMat);

	// tank turret
	TurretBarrelEnd.set(0, 1.0f, turretEndBarrel);
	TurretBarrelEnd *= ScaleMat;
	WorldMat = ScaleMat * BodyRotateMat * Matrix(TRANS, Pos + Vect(0, turretOffset, 0));
	pTurret->SetWorld(WorldMat);

	CamMatrix = TurretRotateMat;

	SetCollidableGroup<PlayerTank>();
	SetColliderModel(pBody->getModel(), AABB);
}

PlayerTank::~PlayerTank()
{
	delete pBody;
	delete pTurret;
}

void PlayerTank::Update()
{
	Reload();

	WorldMat = ScaleMat * BodyRotateMat * Matrix(TRANS, Pos);
	pBody->SetWorld(WorldMat);

	UpdateCollisionData(WorldMat);

	WorldMat = ScaleMat * TurretRotateMat * Matrix(TRANS, Pos + Vect(0, turretOffset, 0));
	pTurret->SetWorld(WorldMat);

	// update cam

	// Direction vector to player
	Vect dir = (Pos - Vect(0, 40.0f, -150.0f) * TurretRotateMat * Matrix(TRANS, Pos)).norm();

	// Angle between the direction and forward
	float angle = (CamMatrix.get(ROW_0).dot(dir)) / (CamMatrix.get(ROW_0).mag() * dir.mag());

	// Rotate turret by angle 
	//CamMatrix *= Matrix(ROT_Y, angle * .03f);
	CamMatrix *= Matrix(ROT_Y, angle);

	SceneManager::GetCurrentScene()->UpdateCameraPos(Vect(0.0f, 1.0f, 0.0f), Pos, Vect(0, 50.0f, -150.0f) * CamMatrix * Matrix(TRANS, Pos));
	
	TurretBarrel = Pos + Vect(0, turretOffset, 0);

	//ScreenLog::Add("Player: X:%.3f, Y:3f, Z:.3f", Pos.X(), Pos.Y(), Pos.Z());
}

void PlayerTank::Draw()
{
	pBody->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
	pTurret->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());

	Visualizer::ShowPoint(TurretBarrel + TurretBarrelEnd * TurretRotateMat, Color::Red);
}

void PlayerTank::Collision(EnemyBullet* )
{
	health--;

	if (health <= 0)
	{
		PlayerManager::PlayerDead();
	}
}

void PlayerTank::CollisionTerrain()
{
	DebugMsg::out("Collision with Terrain\n");
}

void PlayerTank::SceneEntry()
{
	Initialize();
	SubmitUpdateRegistration();
	SubmitDrawRegistration();
	//SubmitKeyRegistration(AZUL_KEY::KEY_3, InputEventType::KEY_PRESS);
	SubmitCollisionRegistration();
}

void PlayerTank::SceneExit()
{
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	//SubmitKeyDeregistration(AZUL_KEY::KEY_SPACE, InputEventType::KEY_PRESS);
	SubmitCollisionDeregistration();
}

void PlayerTank::Initialize()
{
	health = 10;

	// tank body
	Pos.set(0, 0, 20);
	WorldMat = ScaleMat * BodyRotateMat * Matrix(TRANS, Pos);
	pBody->SetWorld(WorldMat);

	UpdateCollisionData(WorldMat);

	// tank turret
	TurretBarrelEnd.set(0, 2.3f, turretEndBarrel);
	TurretBarrelEnd *= ScaleMat;
	WorldMat = ScaleMat * BodyRotateMat * Matrix(TRANS, Pos + Vect(0, turretOffset, 0));
	pTurret->SetWorld(WorldMat);

	CamMatrix = TurretRotateMat;

}

void PlayerTank::MoveForward()
{
	Pos += Vect(0, 0, 1) * BodyRotateMat * speed;
}

void PlayerTank::MoveBackward()
{
	Pos += Vect(0, 0, 1) * BodyRotateMat * -speed;
}

void PlayerTank::TurnLeft()
{
	BodyRotateMat *= Matrix(ROT_Y, rotAngle);
}

void PlayerTank::TurnRight()
{
	BodyRotateMat *= Matrix(ROT_Y, -rotAngle);
}

void PlayerTank::LookUp()
{
	tilt -= rotAngle;

	if (tilt >= -tiltangle)
		TurretRotateMat *= Matrix(ROT_AXIS_ANGLE, TurretRotateMat.get(ROW_0), -rotAngle);
	else
		tilt = -tiltangle;
	DebugMsg::out("%3.1f\n", tilt);
}

void PlayerTank::LookDown()
{
	tilt += rotAngle;

	if (tilt <= tiltangle)
		TurretRotateMat *= Matrix(ROT_AXIS_ANGLE, TurretRotateMat.get(ROW_0), rotAngle);
	else
		tilt = tiltangle;

	DebugMsg::out("%3.1f\n", tilt);
}

void PlayerTank::LookLeft()
{
	TurretRotateMat *= Matrix(ROT_Y, rotAngle);
}

void PlayerTank::LookRight()
{
	TurretRotateMat *= Matrix(ROT_Y, -rotAngle);
}

void PlayerTank::Fire()
{
	if (reloaded)
	{
		BulletFactory::CreatePlayerBullet(TurretRotateMat, TurretBarrel + TurretBarrelEnd * TurretRotateMat);
		reloaded = false;
	}
}

void PlayerTank::Reload()
{
	if(!reloaded)
		reloadtime++;

	if (reloadtime == maxReloadTime)
	{
		reloadtime = 0;
		reloaded = true;
	}
}

int PlayerTank::GetReloadTime()
{
	return reloadtime;
}

Vect PlayerTank::GetPos()
{
	return Pos;
}