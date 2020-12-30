// Drawable for GameObjects

#ifndef _Drawable
#define _Drawable

#include "DrawableManager.h"
#include "RegistrationState.h"

class DrawRegistrationCommand;
class DrawDeregistrationCommand;

class Drawable
{
	friend class DrawableAttorney;
public:
	Drawable();
	virtual ~Drawable();

	/// <summary>
	/// Drawable method used to submit a GameObject for Draw Registration.  Needs to be used so a GameObject will be drawn on screen.
	/// </summary>
	void SubmitDrawRegistration();

	/// <summary>
	/// Drawable method used to submit a GameObject for Draw Deregistration.  GameObject will no longer appear on screen when Deregistered.
	/// </summary>
	void SubmitDrawDeregistration();

private:
	Drawable(const Drawable& other) = delete;
	Drawable& operator=(const Drawable& other) = delete;

	/// <summary>
	/// Drawable method used to draw a 3D GameObject.
	/// </summary>
	virtual void Draw() {};

	/// <summary>
	/// Drawable method used to draw a GameObject that is 2D.
	/// </summary>
	virtual void Draw2D() {};

	/// <summary>
	/// Registers the Drawable to the scene.  Will now be drawn on the screen
	/// </summary>
	void SceneRegistration();

	/// <summary>
	/// Deregisters the Drawble from the scene.  Will no longer be drawn on screen
	/// </summary>
	void SceneDeregistration();

	RegistrationState RegStateCurr;
	DrawableManager::StorageListRef pDeleteRef;
	DrawRegistrationCommand* pRegistrationCmd;
	DrawDeregistrationCommand* pDeregistrationCmd;

};

#endif _Drawable