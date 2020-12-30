// Enemy Bullet

#include "EnemyBullet.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "BulletFactory.h"
#include "BulletAOEFactory.h"

EnemyBullet::EnemyBullet()
	:BulletSpeed(8.0f)
{
	GO_Bullet = new GraphicsObject_TextureFlat(ModelManager::Get("bullet"), ShaderManager::Get("TextureLight"), TextureManager::Get("bullet"));

	ScaleMat.set(SCALE, 0.1f, 0.1f, 0.1f);
	RotateMat.set(IDENTITY);
	Pos.set(0, 20, 0);

	SetCollidableGroup<EnemyBullet>();
	SetColliderModel(GO_Bullet->getModel(), BSPHERE);
}

EnemyBullet::~EnemyBullet()
{
	delete GO_Bullet;
}

void EnemyBullet::SceneEntry()
{
	SubmitAlarmRegistration(ALARM_ID::ALARM_0, 2.0f);
	SubmitUpdateRegistration();
	SubmitDrawRegistration();
	SubmitCollisionRegistration();
}

void EnemyBullet::SceneExit()
{
	SubmitAlarmDeregistration(ALARM_ID::ALARM_0);
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitCollisionDeregistration();

	BulletFactory::BulletReturn(this);
}

void EnemyBullet::Update()
{
	Pos += Vect(0, 0, 1) * RotateMat * BulletSpeed;
	WorldMat = ScaleMat * RotateMat * Matrix(TRANS, Pos);
	GO_Bullet->SetWorld(WorldMat);
	Collidable::UpdateCollisionData(WorldMat);
}

void EnemyBullet::Draw()
{
	GO_Bullet->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}

void EnemyBullet::Alarm0()
{
	SubmitExit();
	BulletAOEFactory::CreateExplosion(Pos);
}

void EnemyBullet::Collision(PlayerTank *)
{
	SubmitExit();
	BulletAOEFactory::CreateExplosion(Pos);
}

void EnemyBullet::Initialize(Matrix rot, Vect pos)
{
	RotateMat = rot;
	Pos = pos;

	WorldMat = ScaleMat * RotateMat * Matrix(TRANS, Pos);

	GO_Bullet->SetWorld(WorldMat);
	UpdateCollisionData(WorldMat);
}