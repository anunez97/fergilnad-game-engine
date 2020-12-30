// Level Two

#ifndef _LevelTwo
#define _LevelTwo

#include "Scene.h"
#include <vector>

class CentralGameManager;
class WorldPlane;

class LevelTwo : public Scene
{
public:
	LevelTwo() = default;
	LevelTwo(const LevelTwo& other) = delete;
	LevelTwo& operator=(const LevelTwo& other) = delete;
	~LevelTwo();

	virtual void Initialize();
	virtual void SceneEnd();

	void SpawnEnemies();

private:
	std::vector<Vect> chaserSpawns;
	std::vector<Vect> rangerSpawns;

	CentralGameManager* pCentralMgr;
	Camera* pCam;

	WorldPlane* pWorldPlane;
};

#endif _LevelTwo