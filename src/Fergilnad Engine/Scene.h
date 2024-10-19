// Scene

#ifndef _Scene
#define _Scene

#include "AzulCore.h"
#include "DrawableManager.h"
#include "UpdatableManager.h"
#include "AlarmableManager.h"
#include "CollisionManager.h"
#include "CameraManager.h"
#include "KeyboardEventManager.h"
#include "SingleKeyEventManager.h"
#include "InputEventType.h"
#include "TerrainManager.h"
#include "TerrainNull.h"

class Updatable;
class Drawable;
class Alarmable;
class CommandBase;
class SceneRegistrationBroker;

class Scene
{
	friend class SceneAttorney;
public:
	Scene();
	Scene(const Scene& other) = default;
	Scene& operator=(const Scene& other) = default;
	virtual ~Scene();

	virtual void Initialize() {};
	virtual void SceneEnd() {};

	/// <summary>
	/// Gets the Scene's current 3D Camera
	/// </summary>
	/// <returns> Returns a pointer the current Scene's 3D Camera object. </returns>
	Camera* GetCurrentCamera();

	/// <summary>
	/// Gets the Scene's current 2D Camera.
	/// </summary>
	/// <returns> Returns a pointer the current Scene's 2D Camera. </returns>
	Camera* GetCurrent2DCamera();

	/// <summary>
	/// Sets the Scene's current Camera
	/// </summary>
	/// <param name="cam"> Pointer to the custom Camera object. </param>
	void SetCurrentCamera(Camera* cam);

	/// <summary>
	/// Updates the Scene's current Camera.
	/// </summary>
	/// <param name="up"> Camera's up vector. </param>
	/// <param name="lookat"> Position that the determines the Camera's forward direction. </param>
	/// <param name="pos"> Position of the Camera. </param>
	void UpdateCameraPos(Vect up, Vect lookat, Vect pos);

	/// <summary>
	/// Sets a terrain to the scene.  Only one terrain can be loaded at a time.
	/// </summary>
	/// <param name="key"> Key for the terrain.  Same key used to load a terrain from the Terrain Manager.</param>
	void SetTerrain(std::string key);

	/// <summary>
	/// Returns the scene's terrain
	/// </summary>
	/// <returns></returns>
	Terrain* GetTerrain();

	/// <summary>
	/// Sets the area that the collision octree will encompass.  The tree will rebuild itself if an object is out of bounds.  
	/// Setting a big enough initial size can reduce the number of rebuilds which can be costly.
	/// </summary>
	/// <param name="length">The side length of the octree, the length is a power of 2, 2^length</param>
	/// <param name="origin">The origin of the octree</param>
	void SetCollisionArea(int length = 10, Vect origin = Vect(0, 0, 0));

private:
	/// <summary>
	/// Updates the scene
	/// </summary>
	void Update();

	/// <summary>
	/// Renders the scene
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// Submits a registration command to the scene
	/// </summary>
	/// <param name="cmd">Pointer to the registration command</param>
	void SubmitCommand(CommandBase* cmd);

	/// <summary>
	/// Registers an Updatable to the scene
	/// </summary>
	/// <param name="up">Pointer to the Updatable</param>
	/// <param name="ref">Entry reference to the list in the UpdatableManager</param>
	void Register(Updatable* up, UpdatableManager::StorageListRef& ref);
	/// <summary>
	/// Deregisters the Updatable from the scene
	/// </summary>
	/// <param name="ref">Entry reference to the list in the UpdatableManager</param>
	void Deregister(UpdatableManager::StorageListRef ref);

	/// <summary>
	/// Registers a Drawable to the scene
	/// </summary>
	/// <param name="up">Pointer to the Drawable</param>
	/// <param name="ref">Entry reference to the list in the DrawableManager</param>
	void Register(Drawable* dr, DrawableManager::StorageListRef& ref);
	/// <summary>
	/// Deregisters the Drawable from the scene
	/// </summary>
	/// <param name="ref">Entry reference to the list in the DrawableManager</param>
	void Deregister(DrawableManager::StorageListRef ref);

	/// <summary>
	/// Registers an Alarmable's alarm
	/// </summary>
	/// <param name="t">Time in seconds before the alarm is triggered</param>
	/// <param name="al">Pointer to the Alarmable</param>
	/// <param name="id">ID of the alarm</param>
	/// <param name="ref">Entry reference to the map in the AlarmableManager</param>
	void Register(float t, Alarmable* al, AlarmableManager::ALARM_ID id, AlarmableManager::StorageEntryRef& ref);
	/// <summary>
	/// Deregisters an Alarmable
	/// </summary>
	/// <param name="ref">Entry reference to the map in the AlarmableManager</param>
	void Deregister(AlarmableManager::StorageEntryRef ref);

	/// <summary>
	/// Registers an Inputable to the scene
	/// </summary>
	/// <param name="in">Pointer to the Inputable</param>
	/// <param name="k">Key to be registered</param>
	/// <param name="e">Input type to be registered</param>
	/// <param name="ref">Entry reference to the list of the SingleKeyEventManager</param>
	void Register(Inputable* in, AZUL_KEY k, InputEventType e, SingleKeyEventManager::StorageRef& ref);
	/// <summary>
	/// Deregisters an Inputable's key and input type from the scene
	/// </summary>
	/// <param name="k">Key to be deregistered</param>
	/// <param name="e">Input type to be deregistered</param>
	/// <param name="ref">Entry reference to the list of the SingleKeyeventManager</param>
	void Deregister(AZUL_KEY k, InputEventType e, SingleKeyEventManager::StorageRef ref);


	UpdatableManager* pUpdateMgr;
	DrawableManager* pDrawMgr;
	AlarmableManager* pAlarmMgr;
	KeyboardEventManager* pKEMgr;
	CollisionManager* pColMgr;
	CameraManager* pCamMgr;
	SceneRegistrationBroker* pRegistrationBrkr;
	Terrain* pTerrain;
	TerrainNull* pTerrainNull;

protected:
	/// <summary>
	/// Sets a collision for two different Collidable types
	/// </summary>
	template<typename C1, typename C2>
	void SetCollisionPair()
	{
		pColMgr->SetCollisionPair<C1, C2>();
	}

	/// <summary>
	/// Sets a collision for a Collidable type against itself
	/// </summary>
	template<typename C>
	void SetCollisionSelf()
	{
		pColMgr->SetCollisionSelf<C>();
	}

	/// <summary>
	/// Sets a collision terrain for a Collidable type
	/// </summary>
	template<typename C>
	void SetCollisionTerrain()
	{
		pColMgr->SetCollisionTerrain<C>();
	}
};

#endif _Scene