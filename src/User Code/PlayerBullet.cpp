// Player Bullet

#include "PlayerBullet.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "BulletFactory.h"
#include "BulletAOEFactory.h"

PlayerBullet::PlayerBullet()
	:BulletSpeed(10.0f)
{
	GO_Bullet = new GraphicsObject_TextureFlat(ModelManager::Get("bullet"), ShaderManager::Get("TextureLight"), TextureManager::Get("bullet"));

	ScaleMat.set(SCALE, 0.1f, 0.1f, 0.1f);
	RotateMat.set(IDENTITY);
	Pos.set(0, 20, 0);

	SetCollidableGroup<PlayerBullet>();
	SetColliderModel(GO_Bullet->getModel(), BSPHERE);
}

PlayerBullet::~PlayerBullet()
{
	delete GO_Bullet;
}

void PlayerBullet::SceneEntry()
{
	SubmitAlarmRegistration(ALARM_ID::ALARM_0, 1.0f);
	SubmitUpdateRegistration();
	SubmitDrawRegistration();
	SubmitCollisionRegistration();
}

void PlayerBullet::SceneExit()
{
	SubmitAlarmDeregistration(ALARM_ID::ALARM_0);
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitCollisionDeregistration();

	BulletFactory::BulletReturn(this);
}

void PlayerBullet::Update()
{
	Pos += Vect(0, 0, 1) * RotateMat * BulletSpeed;
	WorldMat = ScaleMat * RotateMat * Matrix(TRANS, Pos);
	GO_Bullet->SetWorld(WorldMat);
	Collidable::UpdateCollisionData(WorldMat);
}

void PlayerBullet::Draw()
{
	GO_Bullet->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}

void PlayerBullet::Alarm0()
{
	SubmitExit();
	BulletAOEFactory::CreateExplosion(Pos);
}

void PlayerBullet::Collision(EnemyTank*)
{
	SubmitExit();
	BulletAOEFactory::CreateExplosion(Pos);
}

void PlayerBullet::Initialize(Matrix rot, Vect pos)
{
	RotateMat = rot;
	Pos = pos;

	WorldMat = ScaleMat * RotateMat * Matrix(TRANS, Pos);

	GO_Bullet->SetWorld(WorldMat);
	UpdateCollisionData(WorldMat);
}