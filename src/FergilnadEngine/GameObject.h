// GameObject

#ifndef _GameObject
#define _GameObject

#include "AzulCore.h"
#include "Updatable.h"
#include "Drawable.h"
#include "Alarmable.h"
#include "Inputable.h"
#include "Collidable.h"
#include "RegistrationState.h"

class GameObjectEntryCommand;
class GameObjectExitCommand;

class GameObject : public Updatable, public Drawable, public Alarmable, public Inputable, public Collidable
{
	friend class GameObjectAttorney;
public:
	GameObject();
	virtual ~GameObject();

	/// <summary>
	/// Submits a GameObject to be entered into a Scene
	/// </summary>
	void SubmitEntry();

	/// <summary>
	/// Submits a GameObject to be exited from the Scene
	/// </summary>
	void SubmitExit();

	/// <summary>
	/// Enters the GameObject into the Scene
	/// </summary>
	virtual void SceneEntry() {};

	/// <summary>
	/// Method called to exit a GameObject from the Scene.
	/// </summary>
	virtual void SceneExit() {};

private:
	GameObject(const GameObject& other) = default;
	GameObject& operator=(const GameObject & other) = default;

	/// <summary>
	/// Connects the gameobject to the scene
	/// </summary>
	void ConnectToScene();

	/// <summary>
	/// Disconnects the gameobject from the scene
	/// </summary>
	void DisconnectToScene();

	GameObjectEntryCommand* pRegistrationCommand;
	GameObjectExitCommand* pDeregistrationCommand;
	RegistrationState RegStateCurr;
};

#endif _GameObject