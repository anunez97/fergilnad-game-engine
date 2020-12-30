// Level 2

#include "LevelTwo.h"

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

LevelTwo::~LevelTwo()
{
	DebugMsg::out("Level Two destructor\n");
}

void LevelTwo::Initialize()
{
	chaserSpawns = { Vect(419, 0, 498), Vect(496, 0, 498), Vect(654, 0, 645) };
	rangerSpawns = { Vect(615, 0, 0), Vect(145, 0, 185), Vect(165, 0, 641) };

	pWorldPlane = new WorldPlane();

	pCam = new Camera(Camera::Type::PERSPECTIVE_3D);
	pCam->setViewport(0, 0, Fergilnad::GetWidth(), Fergilnad::GetHeight());
	pCam->setPerspective(35.0f, float(Fergilnad::GetWidth()) / float(Fergilnad::GetHeight()), 1.0f, 5000.0f);

	Vect up3DCam(0.0f, 1.0f, 0.0f);
	Vect pos3DCam(50.0f, 50.0f, 150.0f);
	Vect lookAt3DCam(0.0f, 0.0f, 0.0f);

	pCam->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);

	pCentralMgr = new CentralGameManager();

	SetCurrentCamera(pCam);
	GetCurrentCamera()->updateCamera();

	SpawnEnemies();

	// Collisions
	SetCollisionPair<EnemyTank, PlayerBullet>();
	SetCollisionPair<PlayerTank, EnemyBullet>();
}

void LevelTwo::SpawnEnemies()
{
	for (size_t i = 0; i < chaserSpawns.size(); i++)
	{
		EnemyManager::SpawnChaser(chaserSpawns[i]);
	}

	for (size_t i = 0; i < rangerSpawns.size(); i++)
	{
		EnemyManager::SpawnLongRanger(rangerSpawns[i]);
	}
}

void LevelTwo::SceneEnd()
{
	delete pCentralMgr;
	delete pWorldPlane;
}