// SceneDemo

#include "SceneDemo.h"
#include "Frigate.h"
#include "WorldPlane.h"
#include "Tester.h"
#include "Fergilnad.h"
#include "SpriteTest.h"
#include "EnemyTankFactory.h"
#include "PlayerBullet.h"
#include "HUD.h"

void SceneDemo::Initialize()
{
	GOFrig = new Frigate();
	new Frigate();
	//new Frigate();
	//new EnemyTank();
	GOPlane = new WorldPlane();
	//pSprite = new SpriteTest();
	pCam = new Camera(Camera::Type::PERSPECTIVE_3D);
	pCam->setViewport(0, 0, Fergilnad::GetWidth(), Fergilnad::GetHeight());
	pCam->setPerspective(35.0f, float(Fergilnad::GetWidth()) / float(Fergilnad::GetHeight()), 1.0f, 5000.0f);

	Vect up3DCam(0.0f, 1.0f, 0.0f);
	Vect pos3DCam(50.0f, 50.0f, 150.0f);
	Vect lookAt3DCam(0.0f, 0.0f, 0.0f);

	pCam->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
	//pDisplay = new LevelCompleteDisplay();
	pTranCon = new TransitionController();
	SetCollisionSelf<Frigate>();

	SetCurrentCamera(pCam);
	GetCurrentCamera()->updateCamera();
}

void SceneDemo::SceneEnd()
{
	//delete pSprite;
	delete GOFrig;
	delete GOPlane;
	//delete pPlayer;
	//delete pTest;
	//delete pDisplay;
	delete pTranCon;
}

SceneDemo::~SceneDemo()
{
	DebugMsg::out("SceneDemo destructor\n");
}