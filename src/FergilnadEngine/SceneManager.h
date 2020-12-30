// Scene Manager

#ifndef _SceneManager
#define _SceneManager

#include "AzulCore.h"

class Scene;
class SceneChangeCommandBase;
class SceneChangeNullCommand;
class SceneChangeCommand;
class Terrain;

class SceneManager
{
	friend class SceneManagerAttorney;
private:
	static SceneManager* ptrInstance;

	static SceneManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new SceneManager();
		return *ptrInstance;
	}

	SceneManager();
	SceneManager(const SceneManager& other) = delete;
	SceneManager& operator=(const SceneManager& other) = delete;
	~SceneManager() = default;

	/// <summary>
	/// Initializes the start scene
	/// </summary>
	static void InitStartScene();

	/// <summary>
	/// Updates the current scene
	/// </summary>
	static void Update() { Instance().privUpdate(); }
	void privUpdate();

	/// <summary>
	/// Renders any objects or terrain to the scene
	/// </summary>
	static void Draw() { Instance().privDraw(); }
	void privDraw();

	/// <summary>
	/// Deletes the singleton
	/// </summary>
	static void Delete() { Instance().privDelete(); };
	void privDelete();

	/// <summary>
	/// Change the current scene
	/// </summary>
	/// <param name="s"></param>
	void privChangeScene(Scene* s);
	static void ChangeScene(Scene* s) { Instance().privChangeScene(s); }

	/// <summary>
	/// Sets the scene to be changed in the next frame
	/// </summary>
	/// <param name="s"></param>
	void privSetNextScene(Scene* s);

	/// <summary>
	/// Gives the scene's current camera
	/// </summary>
	/// <returns></returns>
	Camera* privGetCamera();

	Scene* pCurrentScene;
	SceneChangeCommandBase* pSceneChangeCmd;
	SceneChangeNullCommand* pSceneNullCmd;
	SceneChangeCommand* pSceneChangeNewCmd;

public:
	/// <summary>
	/// Sets first Scene to be opened when the game starts.
	/// </summary>
	/// <param name="s"> Pointer to the Scene object. </param>
	static void SetStartScene(Scene* s);

	/// <summary>
	/// Gets the Current Scene
	/// </summary>
	/// <returns> Returns a pointer the current Scene. </returns>
	static Scene* GetCurrentScene() { return Instance().pCurrentScene; }

	/// <summary>
	/// Sets the next scene that will be opened.
	/// </summary>
	static void SetNextScene(Scene* s) { Instance().privSetNextScene(s); };

	/// <summary>
	/// Gets the scene's terrain
	/// </summary>
	/// <returns></returns>
	static Terrain* GetTerrain();

	/// <summary>
	/// Gets the scene's current camera
	/// </summary>
	/// <returns></returns>
	static Camera* GetCurrentCamera() { return Instance().privGetCamera(); }
};

#endif _SceneManager