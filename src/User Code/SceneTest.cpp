// Scene Test

#include "SceneTest.h"
#include "CameraManager.h"
#include "Fergilnad.h"
#include "PlayerTank.h"
#include "EnemyTankFactory.h"
#include "EnemyTank.h"
#include "WorldPlane.h"
#include "Tester.h"
#include "Bullet.h"
#include "CentralGameManager.h"
#include "DummyAI.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "PlayerBullet.h"
#include "Terrain.h"
#include "CollisionOctree.h"

SceneTest::SceneTest()
{
}

SceneTest::~SceneTest()
{
	DebugMsg::out("SceneDemo destructor\n");
}

void SceneTest::Initialize()
{
	//pEnemy = new EnemyTank(ModelManager::Get("tankbody"), ModelManager::Get("tankturret"), ShaderManager::Get("TextureLight"), TextureManager::Get("red"));
	//pEnemy->Initialize(Vect(120, 0, 20), new DummyAI(), EnemyTank::Type::CHASER);
	//pEnemy->SubmitEntry();
	//pEnemy2 = new EnemyTank(ModelManager::Get("tankbody"), ModelManager::Get("tankturret"), ShaderManager::Get("TextureLight"), TextureManager::Get("red"));
	//pEnemy2->Initialize(Vect(50, 0, 50), new DummyAI(), EnemyTank::Type::CHASER);
	//pEnemy2->SubmitEntry();
	//pTest = new Tester;
	//pTank = new Tank;
	pCam = new Camera(Camera::Type::PERSPECTIVE_3D);
	pCam->setViewport(0, 0, Fergilnad::GetWidth(), Fergilnad::GetHeight());
	pCam->setPerspective(35.0f, float(Fergilnad::GetWidth()) / float(Fergilnad::GetHeight()), 1.0f, 5000.0f);
	Vect up3DCam(0.0f, 1.0f, 0.0f);
	Vect pos3DCam(50.0f, 50.0f, 150.0f);
	Vect lookAt3DCam(0.0f, 0.0f, 0.0f);
	SetTerrain("terraintest");
	SetCollisionTerrain<PlayerTank>();
	//SetCollisionPair<EnemyTank, Bullet>();
	SetCollisionPair<EnemyTank, PlayerTank>();
	SetCollisionPair<EnemyTank, PlayerBullet>();
	pPlayer = new PlayerTank;
	//pEnemy = new EnemyTank;
	//pEnemy->SetPlayer(pPlayer);
	//pPlane = new WorldPlane;
	pCam->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
	pCentralMgr = new CentralGameManager;
	SetCurrentCamera(pCam);
	GetCurrentCamera()->updateCamera();
	
}

void SceneTest::SceneEnd()
{
	delete pPlayer;
	//delete pPlane;
	//delete pTest;
	//delete pEnemy;
	//delete pEnemy2;
	delete pCentralMgr;
	//delete pTerrain;
}

