// Updatable for GameObjects

#ifndef _Updatable
#define _Updatable

#include "UpdatableManager.h"
#include "RegistrationState.h"

class UpdateRegistrationCommand;
class UpdateDeregistrationCommand;

class Updatable
{
	friend class UpdatableAttorney;
public:
	Updatable();
	virtual ~Updatable();

	/// <summary>
	/// Submits a GameObject to be updated. 
	/// </summary>
	void SubmitUpdateRegistration();

	/// <summary>
	/// Submits a GameObject for Update Deregistration.
	/// </summary>
	void SubmitUpdateDeregistration();

private:
	Updatable(const Updatable& other) = default;
	Updatable& operator=(const Updatable& other) = default;

	virtual void Update() {};

	/// <summary>
	/// Registers the Updatable to the scene
	/// </summary>
	void SceneRegistration();

	/// <summary>
	/// Deregisters the Updatable from the scene
	/// </summary>
	void SceneDeregistration();

	RegistrationState RegStateCurr;
	UpdatableManager::StorageListRef pDeleteRef;
	UpdateRegistrationCommand* pRegistrationCmd;
	UpdateDeregistrationCommand* pDeregistrationCmd;
};

#endif _Updatable