// Bullet

#include "Bullet.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "BulletFactory.h"
#include "CameraManager.h"
#include "SceneManager.h"
#include "Scene.h"

Bullet::Bullet()
	:BulletSpeed(8.0f)
{
	pModel = ModelManager::Get("bullet");
	pShader = ShaderManager::Get("TextureLight");
	pTexture = TextureManager::Get("bullet");
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pBulletLight = new GraphicsObject_TextureFlat(pModel, pShader, pTexture, TextureManager::Get("blue"), TextureManager::Get("blue"), TextureManager::Get("blue"));
	//pBulletLight = new GraphicsObject_ColorNoTexture(pModel, pShader);

	ScaleMat.set(SCALE, 0.1f, 0.1f, 0.1f);
	RotateMat.set(IDENTITY);
	Pos.set(0, 20, 0);

	SetCollidableGroup<Bullet>();
	SetColliderModel(pBulletLight->getModel(), BSPHERE);
}

Bullet::~Bullet()
{
	delete pBulletLight;
}

void Bullet::SceneEntry()
{
	SubmitAlarmRegistration(ALARM_ID::ALARM_0, 3.0f);
	SubmitUpdateRegistration();
	SubmitDrawRegistration();
	SubmitCollisionRegistration();
}

void Bullet::SceneExit()
{
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitCollisionDeregistration();

	//BulletFactory::BulletReturn(this);
}

void Bullet::Update()
{
	Pos += Vect(0, 0, 1) * RotateMat * BulletSpeed;
	WorldMat = ScaleMat * RotateMat * Matrix(TRANS, Pos);
	pBulletLight->SetWorld(WorldMat);
	Collidable::UpdateCollisionData(WorldMat);
}

void Bullet::Draw()
{
	pBulletLight->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}

void Bullet::Alarm0()
{
	//DebugMsg::out("Bullet Alarm went off\n");
	SubmitExit();
}

void Bullet::Collision(EnemyTank* )
{
	SubmitAlarmDeregistration(ALARM_ID::ALARM_0);
	SubmitExit();
}

void Bullet::Initialize(Matrix rot, Vect pos)
{
	RotateMat = rot;
	Pos = pos;

	WorldMat = ScaleMat * RotateMat * Matrix(TRANS, Pos);

	pBulletLight->SetWorld(WorldMat);
	Collidable::UpdateCollisionData(WorldMat);
}