// Frigate

#include "Frigate.h"
#include "FrigateBSphere.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CameraManager.h"
#include "BulletFactory.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TimeManager.h"
#include "SceneTest.h"
#include "CollisionVolumeBSphere.h"
#include "Color.h"
#include "ScreenLog.h"
#include "LevelOne.h"

Frigate::Frigate()
	:ShipTransSpeed(1.0f), ShipRotAng(.05f), BsphereToggle(false), bdebugCol(false)
{
	pModel = ModelManager::Get("SpaceFrigate");
	pShader = ShaderManager::Get("TextureLight");
	pTexture = TextureManager::Get("SpaceFrigate");
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);

	pSpaceFrigateLight = new GraphicsObject_TextureLight(pModel, pShader, pTexture, LightColor, LightPos);
	pBSphere = new FrigateBSphere();

	ScaleMat.set(SCALE, 0.5f, 0.5f, 0.5f);
	//ScaleMat.set(SCALE, 1.0f, 1.0f, 1.0f);
	RotateMat.set(IDENTITY);
	Pos.set(0, 20, 0);

	WorldMat = ScaleMat * RotateMat * Matrix(TRANS, Pos);

	pSpaceFrigateLight->SetWorld(WorldMat);

	up3DCam.set(0.0f, 1.0f, 0.0f);

	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	Alarmable::SubmitAlarmRegistration(ALARM_ID::ALARM_0, 2.0f);
	Alarmable::SubmitAlarmRegistration(ALARM_ID::ALARM_1, 2.0f);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, InputEventType::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_ENTER, InputEventType::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_E, InputEventType::KEY_RELEASE);
	Collidable::SetCollidableGroup<Frigate>();
	Collidable::SubmitCollisionRegistration();
	Collidable::SetColliderModel(pSpaceFrigateLight->getModel(), AABB);
	UpdateCollisionData(WorldMat);
}

void Frigate::Update()
{
	// Ship translation movement (not using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
	{
		Pos += Vect(0, 0, 1) * RotateMat * ShipTransSpeed;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
	{
		Pos += Vect(0, 0, 1) * RotateMat * -ShipTransSpeed;
	}

	// Ship Rotation movement (not using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_A))
	{
		RotateMat *= Matrix(ROT_Y, ShipRotAng);
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_D))
	{
		RotateMat *= Matrix(ROT_Y, -ShipRotAng);
	}

	SceneManager::GetCurrentScene()->UpdateCameraPos(up3DCam, Pos, Pos * Matrix(TRANS, Vect(0, 50.0f, -150.0f)));

	// Spaceship adjust matrix
	WorldMat = ScaleMat * RotateMat * Matrix(TRANS, Pos);
	SetWorld(WorldMat);

	ScreenLog::Add("Frigate: ");
	ScreenLog::Add("\tPos: %3.1f, %3.1f, %3.1f", Pos.X(), Pos.Y(), Pos.Z());

	//Vect vBSSize = GetBSphere().GetRadius() * Vect(1, 1, 1);
	//Vect vBSPos = GetBSphere().GetCenter();

	//Matrix worldBS = Matrix(SCALE, vBSSize) *  Matrix(TRANS, vBSPos);
	//pBSphere->SetWorld(worldBS);
}

void Frigate::Draw()
{
	pSpaceFrigateLight->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());

	//if(bdebugCol)
		//Visualizer::ShowBSphere(GetBSphere(), Color::Red);
	//else
		//Visualizer::ShowBSphere(GetBSphere(), Color::Blue);

	//bdebugCol = false;
}

void Frigate::Alarm0()
{
	//DebugMsg::out("Frigate alarm0 triggered\n");
	//Drawable::SubmitDrawDeregistration();
	//Alarmable::SubmitAlarmRegistration(ALARM_ID::ALARM_0, 2.0f);
	SubmitAlarmRestart(ALARM_ID::ALARM_0, 2.0f);
	//Alarmable::SubmitAlarmDeregistration(ALARM_ID::ALARM_0);
}

void Frigate::Alarm1()
{
	//DebugMsg::out("Frigate alarm1 triggered\n");
	//Drawable::SubmitDrawDeregistration();
	//Alarmable::SubmitAlarmRegistration(ALARM_ID::ALARM_1, 5.0f);
	SubmitAlarmRestart(ALARM_ID::ALARM_1, 5.0f);
	//Alarmable::SubmitAlarmDeregistration(ALARM_ID::ALARM_0);
}

void Frigate::KeyPressed(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_SPACE:
		BulletFactory::CreatePlayerBullet(RotateMat, Pos + (Vect(0, 0, 1) * RotateMat * (pModel->getRadius() / 2.0f)));
		//DebugMsg::out("SPACE key pressed\n");
		break;
	case AZUL_KEY::KEY_ENTER:
		//SceneManager::SetNextScene(new LevelOne);
		SceneManager::SetNextScene(new LevelOne);
		break;
	default:
		DebugMsg::out("ERROR: key %i, unprocessed\n", k);
	}
}

void Frigate::KeyReleased(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_E:
		DebugMsg::out("Frigate deregistered from collision\n");
		Collidable::SubmitCollisionDeregistration();
		break;
	default:
		DebugMsg::out("ERROR: key %i, unprocessed\n", k);
	}
}

void Frigate::Collision(EnemyTank* t)
{
	t;
	bdebugCol = true;
	DebugMsg::out("Collision Frigate with Enemy Tank\n");
}

void Frigate::Collision(Frigate* fr)
{
	fr;
	DebugMsg::out("Collision Frigate with Frigate\n");
}

void Frigate::SetWorld(Matrix world)
{
	pSpaceFrigateLight->SetWorld(world);

	Collidable::UpdateCollisionData(WorldMat);
}

Frigate::~Frigate()
{
	DebugMsg::out("Frigate destructor\n");
	delete pSpaceFrigateLight;
	delete pBSphere;
}