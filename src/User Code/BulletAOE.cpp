// Bullet AOE

#include "BulletAOE.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"

BulletAOE::BulletAOE()
	:maxRadius(5.0f), defaultRadius(1.0f), radiusChange(.1f), radius(1.0f)
{
	Pos.set(0, 0, 0);
	WorldMat = Matrix(SCALE, radius, radius, radius);
	GO_Explosion = new GraphicsObject_TextureFlat(ModelManager::Get("Sphere"), ShaderManager::Get("TextureFlat"), TextureManager::Get("gray"));

	SetCollidableGroup<BulletAOE>();
	SetColliderModel(GO_Explosion->getModel(), BSPHERE);
}

BulletAOE::~BulletAOE()
{
	delete GO_Explosion;
}

void BulletAOE::Draw()
{
	GO_Explosion->Render(SceneManager::GetCurrentCamera());
}

void BulletAOE::Update()
{
	// when the explosion gets big enough destroy it
	if (radius >= maxRadius)
	{
		SubmitExit();
		return;
	}

	radius += radiusChange;

	WorldMat = Matrix(SCALE, radius, radius, radius) * Matrix(TRANS, Pos);
	GO_Explosion->SetWorld(WorldMat);

	UpdateCollisionData(WorldMat);
}

void BulletAOE::Collision(PlayerTank* player)
{
	// damage the player
	player;
}

void BulletAOE::Collision(EnemyTank* enemy)
{
	// damage the enemy
	enemy;
}

void BulletAOE::SceneEntry()
{
	SubmitCollisionRegistration();
	SubmitUpdateRegistration();
	SubmitDrawRegistration();
}

void BulletAOE::SceneExit()
{
	SubmitCollisionDeregistration();
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
}

void BulletAOE::Initialize(Vect pos)
{
	Pos = pos;
	radius = defaultRadius;
	WorldMat = Matrix(SCALE, radius, radius, radius) * Matrix(TRANS, Pos);

	GO_Explosion->SetWorld(WorldMat);

	UpdateCollisionData(WorldMat);
}