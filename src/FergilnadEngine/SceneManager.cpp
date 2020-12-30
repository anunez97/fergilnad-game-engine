// Scene Manager

#include "SceneManager.h"
#include "SceneAttorney.h"
#include "SceneNull.h"
#include "SceneChangeNullCommand.h"
#include "SceneChangeCommand.h"

SceneManager* SceneManager::ptrInstance = nullptr;

SceneManager::SceneManager()
{
	pSceneNullCmd = new SceneChangeNullCommand;
	pSceneChangeNewCmd = new SceneChangeCommand;
	pSceneChangeCmd = pSceneNullCmd;
}

void SceneManager::InitStartScene()
{
	Instance().pCurrentScene->Initialize();
}

void SceneManager::SetStartScene(Scene* ns)
{
	Instance().pCurrentScene = ns;
}

void SceneManager::privUpdate()
{
	pSceneChangeCmd->Execute();

	SceneAttorney::GameLoop::Update(pCurrentScene);
}

void SceneManager::privDraw()
{
	SceneAttorney::GameLoop::Draw(pCurrentScene);
}

void SceneManager::privSetNextScene(Scene* s)
{
	assert(pSceneChangeNewCmd->GetScene() == 0 && "Double Scene Change Attempted\n");

	pSceneChangeNewCmd->SetScene(s);

	pSceneChangeCmd = pSceneChangeNewCmd;
}

void SceneManager::privChangeScene(Scene* s)
{
	pCurrentScene->SceneEnd();

	delete pCurrentScene;

	pCurrentScene = s;

	pCurrentScene->Initialize();

	pSceneChangeCmd = pSceneNullCmd;

	pSceneChangeNewCmd->SetScene(0);
}

Terrain* SceneManager::GetTerrain()
{
	return Instance().pCurrentScene->GetTerrain();
}

Camera* SceneManager::privGetCamera()
{
	return pCurrentScene->GetCurrentCamera();
}

void SceneManager::privDelete()
{
	pCurrentScene->SceneEnd();

	delete pCurrentScene;
	delete pSceneChangeNewCmd;
	delete pSceneNullCmd;

	delete ptrInstance;
	ptrInstance = nullptr;
}