// SceneDemo

#ifndef _SceneDemo
#define _SceneDemo

#include "Scene.h"
#include "LevelCompleteDisplay.h"
#include "TransitionController.h"

class Frigate;
class WorldPlane;
class Tester;
class SpriteTest;
class PlayerTank;

class SceneDemo : public Scene
{
public:
	SceneDemo() = default;
	SceneDemo(const SceneDemo& other) = default;
	SceneDemo& operator=(const SceneDemo& other) = default;
	~SceneDemo();

	virtual void Initialize();
	virtual void SceneEnd();

private:
	Frigate* GOFrig;
	WorldPlane* GOPlane;
	//Tester* pTest;
	Camera* pCam;
	SpriteTest* pSprite;
	PlayerTank* pPlayer;
	LevelCompleteDisplay* pDisplay;
	TransitionController* pTranCon;
};

#endif _SceneDemo