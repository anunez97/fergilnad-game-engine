// Scene Test

#ifndef _SceneTest
#define _SceneTest

#include "Scene.h"

class PlayerTank;
class EnemyTank;
class WorldPlane;
class Camera;
class Tester;
class CentralGameManager;
class Terrain;

class SceneTest : public Scene
{
public:
	SceneTest();
	SceneTest(const SceneTest& other) = delete;
	SceneTest& operator=(const SceneTest& other) = delete;
	~SceneTest();

	virtual void Initialize();
	virtual void SceneEnd();

private:
	PlayerTank* pPlayer;
	EnemyTank* pEnemy;
	EnemyTank* pEnemy2;
	WorldPlane* pPlane;
	Camera* pCam;
	Tester* pTest;
	CentralGameManager* pCentralMgr;
	Terrain* pTerrain;
};

#endif _SceneTest