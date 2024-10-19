// Inputable

#ifndef _Inputable
#define _Inputable

#include "AzulCore.h"
#include "RegistrationState.h"
#include "InputEventType.h"
#include "KeyboardEventManager.h"
#include "SingleKeyEventManager.h"
#include <map>

class InputRegistrationCommand;
class InputDeregistrationCommand;

class Inputable
{
	friend class InputableAttorney;
public:
	Inputable();
	virtual ~Inputable();

	/// <summary>
	/// Submits a Key Registration for a GameObject.
	/// </summary>
	/// <param name="k"> Specific key that will be registered for input. </param>
	/// <param name="e"> Specific event that will be tested for, i.e. KeyPressed, KeyReleased. </param>
	void SubmitKeyRegistration(AZUL_KEY k, InputEventType e);

	/// <summary>
	/// Submits a Key for Deregistration for a GameObject.
	/// </summary>
	/// <param name="k"> Specific key that will be deregistered. </param>
	/// <param name="e"> Specific event that will be tested for, i.e. KeyPressed, KeyReleased. </param>
	void SubmitKeyDeregistration(AZUL_KEY k, InputEventType e);

private:
	Inputable(const Inputable& other) = delete;
	Inputable& operator=(const Inputable& other) = delete;

	virtual void KeyPressed(AZUL_KEY k) { k; };
	virtual void KeyReleased(AZUL_KEY k) { k; };

	struct RegistrationData
	{
		RegistrationState RegStateCurr;
		InputRegistrationCommand* pRegistrationCommand;
		InputDeregistrationCommand* pDeregistrationCommand;
		SingleKeyEventManager::StorageRef pDeleteRef;
	};

	std::map<AZUL_KEY, RegistrationData*> PressMap;
	std::map<AZUL_KEY, RegistrationData*> ReleaseMap;

	/// <summary>
	/// Gives the Registration Data for the key and key event
	/// </summary>
	/// <param name="k">Key that is being tested for</param>
	/// <param name="e">Input type that is being tested for</param>
	/// <returns>Pointer to the Registration Data for the key and input type</returns>
	RegistrationData* GetData(AZUL_KEY k, InputEventType e);

	/// <summary>
	/// Registers the key and input type to be checked for
	/// </summary>
	/// <param name="k">Key that will be checked for</param>
	/// <param name="e">Input type being tested for</param>
	void SceneRegistration(AZUL_KEY k, InputEventType e);

	/// <summary>
	/// Deregisters the key and input type from the scene
	/// </summary>
	/// <param name="k">The key that was being tested for</param>
	/// <param name="e">Input type that was being tested for</param>
	void SceneDeregistration(AZUL_KEY k, InputEventType e);
};

#endif _Inputable