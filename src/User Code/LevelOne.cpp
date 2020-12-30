// Level 1

#include "LevelOne.h"

#include "Fergilnad.h"
#include "CentralGameManager.h"
#include "EnemyTankFactory.h"
#include "WorldPlane.h"

#include "EnemyManager.h"
#include "PlayerManager.h"

#include "PlayerTank.h"
#include "EnemyTank.h"
#include "EnemyBullet.h"
#include "PlayerBullet.h"

LevelOne::~LevelOne()
{
	DebugMsg::out("Level One destructor\n");
}

void LevelOne::Initialize()
{
	rangerSpawns = { Vect(615, 0, 0)/*, Vect(145, 0, 185), Vect(165, 0, 641) */};

	//pWorldPlane = new WorldPlane();

	pCam = new Camera(Camera::Type::PERSPECTIVE_3D);
	pCam->setViewport(0, 0, Fergilnad::GetWidth(), Fergilnad::GetHeight());
	pCam->setPerspective(35.0f, float(Fergilnad::GetWidth()) / float(Fergilnad::GetHeight()), 1.0f, 5000.0f);

	Vect up3DCam(0.0f, 1.0f, 0.0f);
	Vect pos3DCam(50.0f, 50.0f, 150.0f);
	Vect lookAt3DCam(0.0f, 0.0f, 0.0f);

	pCam->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);

	pCentralMgr = new CentralGameManager();
	SpawnEnemies();

	// Collisions
	SetCollisionPair<EnemyTank, PlayerBullet>();
	SetCollisionArea(5);
	//SetCollisionPair<PlayerTank, EnemyBullet>();

	SetCurrentCamera(pCam);
	GetCurrentCamera()->updateCamera();
}

void LevelOne::SpawnEnemies()
{
	for (size_t i = 0; i < rangerSpawns.size(); i++)
	{
		EnemyManager::SpawnLongRanger(rangerSpawns[i]);
	}
}

void LevelOne::SceneEnd()
{
	delete pCentralMgr;
	//delete pWorldPlane;
}