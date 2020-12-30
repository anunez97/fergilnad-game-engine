// Level 1

#ifndef _LevelOne
#define _LevelOne

#include "Scene.h"
#include <vector>

class CentralGameManager;
class WorldPlane;
class PlayerTank;

class LevelOne : public Scene
{
public:
	LevelOne() = default;
	LevelOne(const LevelOne& other) = default;
	LevelOne& operator=(const LevelOne& other) = default;
	~LevelOne();

	virtual void Initialize();
	virtual void SceneEnd();

	void SpawnEnemies();

private:
	std::vector<Vect> rangerSpawns;

	CentralGameManager* pCentralMgr;
	Camera* pCam;
	//WorldPlane* pWorldPlane;
};

#endif _LevelOne