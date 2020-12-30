// Scene

#include "Scene.h"
#include "SceneRegistrationBroker.h"

Scene::Scene()
{
	pUpdateMgr = new UpdatableManager;
	pDrawMgr = new DrawableManager;
	pAlarmMgr = new AlarmableManager;
	pKEMgr = new KeyboardEventManager;
	pColMgr = new CollisionManager;
	pCamMgr = new CameraManager;
	pRegistrationBrkr = new SceneRegistrationBroker;
	pTerrainNull = new TerrainNull();
	pTerrain = pTerrainNull;
}

void Scene::Update()
{
	pRegistrationBrkr->ExecuteCommands();

	pColMgr->ProcessCollisions();

	pKEMgr->ProcessKeyEvents();

	pAlarmMgr->ProcessAlarms();

	pUpdateMgr->ProcessElements();
}

void Scene::Draw()
{
	pTerrain->Render(pCamMgr->GetCurrentCamera());

	pDrawMgr->ProcessElements();
}

void Scene::Register(Updatable* up, UpdatableManager::StorageListRef& ref)
{
	pUpdateMgr->Register(up, ref);
}

void Scene::Deregister(UpdatableManager::StorageListRef ref)
{
	pUpdateMgr->Deregister(ref);
}

void Scene::Register(Drawable* dr, DrawableManager::StorageListRef& ref)
{
	pDrawMgr->Register(dr, ref);
}

void Scene::Deregister(DrawableManager::StorageListRef ref)
{
	pDrawMgr->Deregister(ref);
}

void Scene::Register(float t, Alarmable* al, AlarmableManager::ALARM_ID id, AlarmableManager::StorageEntryRef& ref)
{
	pAlarmMgr->Register(t, al, id, ref);
}

void Scene::Deregister(AlarmableManager::StorageEntryRef ref)
{
	pAlarmMgr->Deregister(ref);
}

void Scene::Register(Inputable* in, AZUL_KEY k, InputEventType e, SingleKeyEventManager::StorageRef& ref)
{
	pKEMgr->Register(in, k, e, ref);
}

void Scene::Deregister(AZUL_KEY k, InputEventType e, SingleKeyEventManager::StorageRef ref)
{
	pKEMgr->Deregister(k, e, ref);
}

void Scene::SubmitCommand(CommandBase* cmd)
{
	pRegistrationBrkr->addCommand(cmd);
}

Camera* Scene::GetCurrentCamera()
{
	return pCamMgr->GetCurrentCamera();
}

Camera* Scene::GetCurrent2DCamera()
{
	return pCamMgr->GetCurrentCamera2D();
}

void Scene::SetCurrentCamera(Camera* cam)
{
	pCamMgr->SetCurrentCamera(cam);
}

void Scene::UpdateCameraPos(Vect up, Vect lookat, Vect pos)
{
	pCamMgr->SetOrientAndPosition(up, lookat, pos);
}

void Scene::SetTerrain(std::string key)
{
	pTerrain = TerrainManager::Get(key);
}

Terrain* Scene::GetTerrain()
{
	return pTerrain;
}

void Scene::SetCollisionArea(int size, Vect origin)
{
	pColMgr->SetCollisionArea(size, origin);
}

Scene::~Scene()
{
	DebugMsg::out("Scene destructor\n");
	delete pUpdateMgr;
	delete pDrawMgr;
	delete pAlarmMgr;
	delete pKEMgr;
	delete pColMgr;
	delete pCamMgr;
	delete pRegistrationBrkr;
	delete pTerrainNull;
}