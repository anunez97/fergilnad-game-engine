// Tank

#include "Tank.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "BulletFactory.h"
#include "SceneTest.h"

Tank::Tank()
	:speed(1.0f), rotAngle(0.05f), turretOffset(7.0f), turretend(0, 2.0f, 15.0f)
{
	Vect color(1.5f, 1.5f, 1.5f);
	Vect lightpos(1.0f, 1.0f, 1.0f);

	pBody = new GraphicsObject_TextureFlat(ModelManager::Get("tank2"), ShaderManager::Get("TextureLight"), TextureManager::Get("red"), TextureManager::Get("red"), TextureManager::Get("red"));
	//pTurret = new GraphicsObject_TextureFlat(ModelManager::Get("tankturret"), ShaderManager::Get("TextureFlat"), TextureManager::Get("darkblue"), TextureManager::Get("blue"), TextureManager::Get("blue"));

	//ScaleMat.set(SCALE, 0.05f, 0.05f, 0.05f);
	ScaleMat.set(SCALE, 0.5f, 0.5f, 0.5f);
	RotateMat.set(ROT_X, 30.0f);

	// tank body
	Pos.set(-100, -50, -100);
	WorldMat = ScaleMat * RotateMat * Matrix(TRANS, Pos);
	pBody->SetWorld(WorldMat);

	/*// tank turret
	WorldMat = ScaleMat * RotateMat * Matrix(TRANS, Pos + Vect(0, turretOffset, 0));
	pTurret->SetWorld(WorldMat);
	//*/
	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	//Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, EVENT_TYPE::KEY_PRESS);
	//Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_ENTER, EVENT_TYPE::KEY_PRESS);
	Collidable::SetCollidableGroup<Tank>();
	Collidable::SetColliderModel(pBody->getModel(), AABB);
	//Collidable::SubmitCollisionRegistration();

	//UpdateCollisionData(WorldMat);
}

Tank::~Tank()
{
	delete pBody;
	//delete pTurret;
}

void Tank::Update()
{
	/*
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
	{
		Pos += Vect(0, 0, 1) * RotateMat * speed;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
	{
		Pos += Vect(0, 0, 1) * RotateMat * -speed;
	}

	if (Keyboard::GetKeyState(AZUL_KEY::KEY_A))
	{
		RotateMat *= Matrix(ROT_Y, rotAngle);
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_D))
	{
		RotateMat *= Matrix(ROT_Y, -rotAngle);
	}*/
	//RotateMat *= Matrix(ROT_X, 0.01f);
	//SceneManager::GetCurrentScene()->UpdateCameraPos(Vect(0.0f, 1.0f, 0.0f), Pos, Pos * Matrix(TRANS, Vect(0, 50.0f, -150.0f)));

	WorldMat = ScaleMat * RotateMat * Matrix(TRANS, Pos);
	pBody->SetWorld(WorldMat);

	UpdateCollisionData(WorldMat);

	//WorldMat = ScaleMat * Matrix(IDENTITY) * Matrix(TRANS, Pos + Vect(0, turretOffset, 0));
	//pTurret->SetWorld(WorldMat);
}

void Tank::Draw()
{
	//ShowNode();
	pBody->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
	//pTurret->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}

void Tank::KeyPressed(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_SPACE:
		//BulletFactory::CreateBullet(RotateMat, Pos + Vect(0, turretOffset, 0));
		break;
	case AZUL_KEY::KEY_ENTER:
		SceneManager::SetNextScene(new SceneTest);
	}
}

void Tank::KeyReleased(AZUL_KEY k)
{
	k;
}

void Tank::Collision(Frigate* fri)
{
	fri;
	DebugMsg::out("Collision Tank with Frigate\n");
}

void Tank::Collision(Tank* t)
{
	t;
	DebugMsg::out("Collision Tank with Tank\n");
}

void Tank::MoveTo(Vect pos)
{
	this->Pos = pos;
	WorldMat = ScaleMat * RotateMat * Matrix(TRANS, Pos);
	UpdateCollisionData(WorldMat);
}

void Tank::RegisterCollision()
{
	SubmitCollisionRegistration();
}

void Tank::UpdateWorld(Matrix rotate, Vect pos)
{
	WorldMat = ScaleMat, rotate, Matrix(TRANS, Pos);
	pBody->SetWorld(WorldMat);

	//WorldMat = ScaleMat * Matrix(IDENTITY) * Matrix(TRANS, Pos + Vect(0, turretOffset, 0));
	//pTurret->SetWorld(WorldMat);
}